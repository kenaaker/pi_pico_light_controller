#ifndef PI_PICO_GPIO_H
#define PI_PICO_GPIO_H

#include <string>
#include <stdint.h>

typedef enum e_pi_pico_gpio {
     e_pi_pico_gpio_0,
     e_pi_pico_gpio_1,
     e_pi_pico_gpio_2,
     e_pi_pico_gpio_3,
     e_pi_pico_gpio_4,
     e_pi_pico_gpio_5,
     e_pi_pico_gpio_6,
     e_pi_pico_gpio_7,
     e_pi_pico_gpio_8,
     e_pi_pico_gpio_9,
    e_pi_pico_gpio_10,
    e_pi_pico_gpio_11,
    e_pi_pico_gpio_12,
    e_pi_pico_gpio_13,
    e_pi_pico_gpio_14,
    e_pi_pico_gpio_15,
    e_pi_pico_gpio_16,
    e_pi_pico_gpio_17,
    e_pi_pico_gpio_18,
    e_pi_pico_gpio_19,
    e_pi_pico_gpio_20,
    e_pi_pico_gpio_21,
    e_pi_pico_gpio_22,
    e_pi_pico_gpio_23,
    e_pi_pico_gpio_24,
    e_pi_pico_gpio_25,
    e_pi_pico_gpio_26,
    e_pi_pico_gpio_27,
    e_pi_pico_gpio_28,
    e_pi_pico_gpio_MAX
} e_pi_pico_gpio_t;

#include <hardware/gpio.h>
class pi_pico_gpio {
public:
    pi_pico_gpio();
    pi_pico_gpio(e_pi_pico_gpio g_id);
    ~pi_pico_gpio();
    void pi_pico_gpio_on(void);
    void pi_pico_gpio_off(void);
    bool gpio_set_value(bool on_or_off);
private:
    std::string gpio_pin_name;
    std::string gpio_pin;
    e_pi_pico_gpio gpio_id;
    bool gpio_state;
};

#endif /* PI_PICO_GPIO_H */
