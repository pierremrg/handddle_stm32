#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim4;

extern uint16_t state_buzzer;

void set_buzzer()
{
	state_buzzer = 1;
	int dutycycle_buzzer = 50;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	htim4.Instance->CCR1 = dutycycle_buzzer; //PWM Rate might change

	HAL_Delay(500);

	dutycycle_buzzer = 0;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	htim4.Instance->CCR1 = dutycycle_buzzer; //PWM Rate might change

	HAL_Delay(500);
}

void send_buzzer_state()
{
	send_sec_msg_buzzer_state(state_buzzer,&huart2);
}
