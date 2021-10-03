#include "../../Core/Inc/main.h"

extern int light;

void set_shutdown_breakdown()
{
	int shutdown_pwm = 0;
	set_cooling(&shutdown_pwm);
	set_heater_pwm(&shutdown_pwm);
	set_heater(&shutdown_pwm);

	set_buzzer();

	light = 6;
	set_lights(light);
}

void set_shutdown_all()
{
	int shutdown_pwm = 0;
	set_cooling(&shutdown_pwm);
	set_heater_pwm(&shutdown_pwm);
	set_heater(&shutdown_pwm);

	light = 8;
	set_lights(light);

}
