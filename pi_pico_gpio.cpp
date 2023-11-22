
#include <iostream>
#include <stdlib.h>

#include "pi_pico_gpio.h"

const static std::string GPIO_PIN_NAMES[e_pi_pico_gpio_MAX + 1] = {
     "GPIO_0",
     "GPIO_1",
     "GPIO_2",
     "GPIO_3",
     "GPIO_4",
     "GPIO_5",
     "GPIO_6",
     "GPIO_7",
     "GPIO_8",
     "GPIO_9",
    "GPIO_10",
    "GPIO_11",
    "GPIO_12",
    "GPIO_13",
    "GPIO_14",
    "GPIO_15",
    "GPIO_16",
    "GPIO_17",
    "GPIO_18",
    "GPIO_19",
    "GPIO_20",
    "GPIO_21",
    "GPIO_22",
    "GPIO_23",
    "GPIO_24",
    "GPIO_25",
    "GPIO_26",
    "GPIO_27",
    "GPIO_28",
    "GPIO_MAX"
};

pi_pico_gpio::pi_pico_gpio() {
    gpio_pin_name = "GPIO_0";
    gpio_pin = "gpio_0";
    gpio_state = false;
    gpio_id = e_pi_pico_gpio_0;
}

pi_pico_gpio::~pi_pico_gpio() {
}

/* Create the control structure to setup, run, and shutdown a pwm_light  */
/* Attached to a GPIO pin */
pi_pico_gpio::pi_pico_gpio(e_pi_pico_gpio_t g_id) {
    if (g_id >= e_pi_pico_gpio_0 && (g_id < e_pi_pico_gpio_MAX)) {
        gpio_pin_name = GPIO_PIN_NAMES[g_id];
    }
    switch (g_id) {
    default:
        std::cout << __func__ << ":" << __LINE__ << " Invalid GPIO pin ID.";
        break;
    } /* endswitch */
}

bool pi_pico_gpio::gpio_set_value(bool on_or_off) {
    bool ret_value;

    ret_value = false;
    return ret_value;
}


/* The expected range here is 0 <= brightness <= 100 */
void pi_pico_gpio::pi_pico_gpio_on(void) {
    gpio_set_value(true);
}

void pi_pico_gpio::pi_pico_gpio_off(void) {
    gpio_set_value(false);
}

