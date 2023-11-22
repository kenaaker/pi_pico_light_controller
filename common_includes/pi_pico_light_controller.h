#ifndef PI_PICO_LIGHT_CONTROLLER_H
#define PI_PICO_LIGHT_CONTROLLER_H

#include <iostream>

#include "ad_in_converter.h"
#include "light_state_determiner.h"
#include "transport_record.h"
#include "pi_pico_gpio.h"

#include "timer.h"

class pi_pico_light_controller {
public:
    pi_pico_light_controller(void);
    ~pi_pico_light_controller(void);

    void user_toggle_setting(light_states new_light_state);

    light_states get_physical_light_state(void);
    light_states set_physical_light_state(light_states new_light_state);

    void dimmer_setting_changed(int value);

    pi_pico_gpio *get_PIR_gpio(void) {
        return PIR_gpio;
    }

    pi_pico_gpio *set_PIR_gpio(pi_pico_gpio *new_value) {
        pi_pico_gpio *ret_value;

        std::cout << __func__ << ":" << __LINE__;
        ret_value = PIR_gpio;
        PIR_gpio = new_value;
        std::cout << __func__ << ":" << __LINE__;
        return ret_value;
    }

    pi_pico_gpio *get_power_control_gpio(void) {
        return power_control_gpio;
    }

    pi_pico_gpio *set_power_control_gpio(pi_pico_gpio *new_value) {
        pi_pico_gpio *ret_value;

        std::cout << __func__ << ":" << __LINE__;
        ret_value = power_control_gpio;
        power_control_gpio = new_value;
        std::cout << __func__ << ":" << __LINE__;
        return ret_value;
    }
    void user_set_light_to_default(void) {
        light_state_d.user_set_light_to_default();
    }
    void send_values_to_remote(light_controller_object::light_controller_values_t values) {
        // cmd_server_socket.send_values_to_socket(&values);
        ;
    }
private:
    light_state_determiner light_state_d;
    timer *light_sensor_poll;
    timer *power_supply_voltage_poll;
    timer *light_state_poll;
    ad_in_converter light_intensity_converter;
    ad_in_converter power_supply_voltage_converter;
    var_st_xport<light_controller_remote_hdr_t, 'L', 4,
                 sizeof(light_controller_remote_transport_body_t),
                 light_controller_remote_transport_body_t>
        light_controller_shared_data;
    std::string PIR_gpio_value; /* PIR detector GPIO value. */
    pi_pico_gpio *PIR_gpio;
    pi_pico_gpio *power_control_gpio;
    light_controller_object light_controller_class_object;
    void on_actionClose_triggered();
};

pi_pico_light_controller light_controller;

#endif // PI_PICO_LIGHT_CONTROLLER_H
