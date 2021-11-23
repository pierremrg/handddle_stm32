#include "../../Lib/inc/Cooling.h"

#include "../../Core/Inc/main.h"

#define STOP 0

extern TIM_HandleTypeDef htim4;



void set_cooling(int dutycycle)
{
	set_heater(STOP);
	set_heater_pwm(STOP);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	htim4.Instance->CCR2 = dutycycle; //PWM Rate might change
}

void get_tachy_cooling()
{

}
