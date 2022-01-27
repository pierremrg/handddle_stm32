#include "../../Lib/inc/Cooling.h"

#include "../../Core/Inc/main.h"

#define STOP 0

extern TIM_HandleTypeDef htim4;
int heater_actif;



void set_cooling(int dutycycle)
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	htim4.Instance->CCR2 = dutycycle; //PWM Rate might change
}

void get_tachy_cooling()
{

}

void cooling_stop()
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	htim4.Instance->CCR2 = STOP; //PWM Rate might change
}
