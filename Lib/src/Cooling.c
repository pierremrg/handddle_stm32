#include "../../Lib/inc/Cooling.h"

#include "../../Core/Inc/main.h"

extern TIM_HandleTypeDef htim4;


void set_cooling(int *ptr_dutycycle)
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	htim4.Instance->CCR2 = *ptr_dutycycle; //PWM Rate might change
}
