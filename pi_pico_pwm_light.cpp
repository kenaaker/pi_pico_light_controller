
#include <iostream>
#include <stdlib.h>

#include "pi_pico_pwm_light.h"
// #include "pwm.h"

pi_pico_pwm_light::pi_pico_pwm_light() {
    pi_pico_pwm_pin = "Uninit";
    pi_pico_pwm_light_brightness = 100;
}

pi_pico_pwm_light::~pi_pico_pwm_light() {
//    delete dc;
}

/* Create the control structure to setup, run, and shutdown a pwm_light  */
/* Attached to a GPIO pin */
pi_pico_pwm_light::pi_pico_pwm_light(e_pwm_light_id m_id) {
    switch (m_id) {
    case e_pwm_light_id::e_pwm_light_1:
        pi_pico_pwm_pin = pwm_light_1_pin;
        break;
    case e_pwm_light_id::e_pwm_light_2:
        pi_pico_pwm_pin = pwm_light_2_pin;
        break;
    default:
        std::cout << __func__ << ":" << __LINE__ << " Invalid pwm_light ID.";
        std::exit;
        break;
    } /* endswitch */
    pi_pico_pwm_light_id = m_id;
    pi_pico_pwm_light_brightness = 0;
//    dc = nullptr;
}


/* The expected range here is 0 <= brightness <= 100 */
void pi_pico_pwm_light::pi_pico_pwm_light_on(unsigned int brightness) {

//    pi_pico_dc->set_duty_cycle(brightness);
    pi_pico_pwm_light_brightness = brightness;
}

void pi_pico_pwm_light::pi_pico_pwm_light_off(void) {
    pi_pico_pwm_light_on(0);
}

int pi_pico_pwm_light::pi_pico_pwm_light_get_brightness() {
    return pi_pico_pwm_light_brightness;
}

void pi_pico_pwm_light::pi_pico_pwm_light_set_brightness(int new_brightness) {
    pi_pico_pwm_light_on(new_brightness);
    pi_pico_pwm_light_brightness = new_brightness;
}
