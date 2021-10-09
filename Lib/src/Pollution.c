#include "../../Lib/inc/Pollution.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"
#include <string.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern uint16_t pm10[1] ;
extern uint16_t pm25[1] ;
extern uint16_t pm100[1] ;

uint8_t UART1_rxBuffer[33] = {0};
uint8_t UART1_manip_33[33] = {0};
uint8_t UART1_manip_32[32] = {0};


void get_pollution ()
{

	struct pms5003data {
	  uint16_t framelen;
	  uint16_t pm10_standard, pm25_standard, pm100_standard;
	  uint16_t pm10_env, pm25_env, pm100_env;
	  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
	  uint16_t unused;
	  uint16_t checksum;
	};

	struct pms5003data data;

	HAL_UART_Receive(&huart1, UART1_rxBuffer, 33, 1000);

	// Si UART1_rxBuffer commence par 0x42 sur l'octet 1 et 2 alors on fait un décalage de tableau pour refaire un
	// tableau de 32 bytes qui correspond à une trame correcte
	// De même si on a un le "bit de fin" qui est au debut et à la fin de la trame on décale et on retire le dernier byte
	for (int i = 0; i<33 ; i++)
	{
	  UART1_manip_33[i] = UART1_rxBuffer[i];
	}

	if(UART1_manip_33[0] == UART1_manip_33[1] || (UART1_manip_33[0] != 66 && UART1_manip_33[33] != 66))
	{
	  for (int i = 1 ; i<33; i++)
	  {
		  if(i!=33)
			  UART1_manip_33[i-1] = UART1_manip_33[i];
		  else
			  UART1_manip_33[i]=0; //Possiblement pas besoin de mettre la dernière case à 0 car je la vire
	  }
	}

	for (int i = 0 ; i<32; i++)
	{
	  UART1_manip_32[i] = UART1_manip_33[i];
	}

	// The data comes in endian'd, this solves it so it works on all platforms
	uint16_t buffer_u16[15];
	uint16_t buffer_test[3];
	for (uint8_t i = 0; i < 15; i++)
	{
	 buffer_u16[i] = UART1_manip_32[2 + i * 2 + 1];
	 buffer_u16[i] += (UART1_manip_32[2 + i * 2] << 8);
	}

	for (int i = 0; i<3; i++)
		{
			buffer_test[i] = buffer_u16[i+1];
		}

	if((buffer_u16[1] == 0) | (buffer_u16[1] > (pm10[0] + 500) ) )
		pm10[0] = pm10[0];
	else
		pm10[0] = buffer_test[0];

	if((buffer_u16[2] == 0) | ( buffer_u16[2] > (pm25[0] + 500) ))
			pm25[0] = pm25[0];
		else
			pm25[0] = buffer_test[1];

	if((buffer_u16[3] == 0) | ( buffer_u16[3] > (pm100[0] + 500) ) )
			pm100[0] = pm100[0];
		else
			pm100[0] = buffer_test[2];

	// put it into a nice struct :)
	memcpy((void *)&data, (void *)buffer_u16, 30);


}

void send_pollution()
{
	send_main_msg_pollution(*pm10, *pm25, *pm100, &huart2);;
}

