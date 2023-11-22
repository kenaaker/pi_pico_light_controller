#include "pi_pico_light_controller.h"
#include "timer.h"
#include "light_controller_object.h"
#include "light_state_determiner.h"
#include "transport_record.h"


static void command_proc_backend(const light_controller_remote_hdr *,
                                 const void *remote_opcode_and_values,
                                 const void *pi_pico_light_controller
                                 ) {


    light_controller_remote_transport_body_t local_remote_opcode_and_values =
        *(light_controller_remote_transport_body_t *)remote_opcode_and_values;
    light_controller_object::light_controller_values_t local_object_values;
    class pi_pico_light_controller *local_pi_pico_light_controller = (class pi_pico_light_controller *)pi_pico_light_controller;

    light_states current_light_state = light_controller.get_physical_light_state();
    command_opcode_enum_t local_command_opcode;

    /* local_object_values = local_remote_opcode_and_values.remote_values; */

    local_object_values.PIR_detected_presence = local_remote_opcode_and_values.remote_values.PIR_detected_presence;
    local_object_values.dimmer_setting = local_remote_opcode_and_values.remote_values.dimmer_setting;
    local_object_values.light_intensity = local_remote_opcode_and_values.remote_values.light_intensity;
    local_object_values.physical_light_state = local_remote_opcode_and_values.remote_values.physical_light_state;
    local_object_values.user_set_light_state = local_remote_opcode_and_values.remote_values.user_set_light_state;

    local_command_opcode = local_remote_opcode_and_values.command_opcode;

    /* Need to merge passed in remote_values and local shared remote values before we do anything else */
    if (local_command_opcode == command_opcode_toggle_on_off) {
        if (current_light_state == light_off) {
            local_pi_pico_light_controller->user_toggle_setting(light_on);
        } else if (current_light_state == light_on) {
            local_pi_pico_light_controller->user_toggle_setting(light_off);
        } else if (current_light_state == undefined_light_state) {
            std::cout << __func__ << ":" << __LINE__ << " Setting light on from undefined state.";
            local_pi_pico_light_controller->user_toggle_setting(light_on);
        } else {
            std::cout << __func__ << ":" << __LINE__ << "Don't understand the toggle command = " << local_command_opcode;
            std::cout << __func__ << ":" << __LINE__ << "current_light_state = " << current_light_state;
        }
    } else if (local_command_opcode == command_opcode_reset_to_default) {
        std::cout << __func__ << ":" << __LINE__ << "reset_to_default is the opcode ";
        local_pi_pico_light_controller->user_set_light_to_default();
    } else if (local_command_opcode == command_opcode_get_light_state) {
        // std::cout << __func__ << ":" << __LINE__ << "get_light_state is the opcode";

        local_object_values.PIR_detected_presence = light_controller.get_PIR_detected_presence();
        local_object_values.dimmer_setting = light_controller.get_dimmer_setting();
        local_object_values.power_supply_voltage = light_controller.get_power_supply_voltage();
        local_object_values.light_intensity = light_controller.get_light_intensity();
        local_object_values.physical_light_state = light_controller.get_physical_light_state();
        local_object_values.user_set_light_state = light_controller.get_user_set_light_state();
        local_pi_pico_light_controller->send_values_to_remote(local_object_values);
    } else if (local_command_opcode == command_opcode_dimmer_setting) {
        std::cout << __func__ << ":" << __LINE__ << "dimmer_setting command = " << local_command_opcode;
        local_pi_pico_light_controller->dimmer_setting_changed(local_object_values.dimmer_setting);
    } else {
        std::cout << __func__ << ":" << __LINE__ << "Didn't understand cmd = " << local_command_opcode;
    }
} /* command_proc_backend */

static bool light_sensor_poll_callback(std::chrono::milliseconds light_sensor_polling_interval) {

      std::cout << __func__ << ":" << __LINE__ << "Read from light intensity converter poll callback`. " << std::endl;
//    std::cout << __func__ << ":" << __LINE__ << "Read from light intensity converter = " << light_intensity_converter.converter_read(); << std::endl;
      return true;
}

static bool power_supply_voltage_poll_callback(std::chrono::milliseconds power_supply_polling_interval) {

      std::cout << __func__ << ":" << __LINE__ << "Read from light intensity converter poll callback`. " << std::endl;
//    std::cout << __func__ << ":" << __LINE__ << "Read from light intensity converter = " << light_intensity_converter.converter_read(); << std::endl;
      return true;
}
pi_pico_light_controller::pi_pico_light_controller(void) {
    std::string PIR_gpio_value_path;

    PIR_gpio = new pi_pico_gpio(e_pi_pico_gpio_17);

    power_control_gpio = new pi_pico_gpio(e_pi_pico_gpio_4);
    power_control_gpio->pi_pico_gpio_off();

    light_intensity_converter.set_ain_channel(0);
    light_intensity_converter.set_instrument_name("light intensity");
    light_intensity_converter.set_lower_bound(255);
    light_intensity_converter.set_upper_bound(0);

    light_state_d.set_turn_on_low_bound(50);
    light_state_d.set_turn_off_high_bound(60);
    light_state_d.user_set_light_to_default();

    power_supply_voltage_converter.set_ain_channel(1);
    power_supply_voltage_converter.set_instrument_name("power supply_voltage");
    power_supply_voltage_converter.set_lower_bound(0);
    power_supply_voltage_converter.set_upper_bound(12);

    light_sensor_poll = new timer;

    light_sensor_poll->add_callback(light_sensor_poll_callback, std::chrono::milliseconds(100));

    std::cout << __func__ << ":" << __LINE__ << " Setting up timer for polling power supply voltage.";
    power_supply_voltage_poll = new timer;

    power_supply_voltage_poll->add_callback(power_supply_voltage_poll_callback, std::chrono::milliseconds(500));

 }

pi_pico_light_controller::~pi_pico_light_controller(void) {

    light_controller_class_object.set_physical_light_state(light_off);
}

void pi_pico_light_controller::on_actionClose_triggered() {
    light_controller_class_object.set_physical_light_state(light_off);
    exit(0);
}

void pi_pico_light_controller::dimmer_setting_changed(int new_dimmer_setting) {
    std::cout << __func__ << ":" << __LINE__ << " new_dimmer_setting =" << new_dimmer_setting;
    light_controller_class_object.set_dimmer_setting(new_dimmer_setting);
}

void pi_pico_light_controller::user_toggle_setting(light_states new_light_state) {
    std::cout << __func__ << ":" << __LINE__ << " new_light_state is " << new_light_state;
    switch (new_light_state) {
    case light_on:
        light_state_d.user_set_light_on();
        std::cout << __func__ << ":" << __LINE__ << " light state should be " << light_on;
        light_controller_class_object.set_user_set_light_state(new_light_state);
        power_control_gpio->gpio_set_value(1);
        std::cout << __func__ << ":" << __LINE__;
        break;
    case light_off:
        light_state_d.user_set_light_off();
        std::cout << __func__ << ":" << __LINE__ << " light state should be " << light_off;
        light_controller_class_object.set_user_set_light_state(new_light_state);
        power_control_gpio->gpio_set_value(0);
        break;
    case undefined_light_state:
        light_state_d.user_set_light_to_default();
        break;
    default:
        std::cout << __func__ << ":" << __LINE__ << " light state toggle is confused." << "light state = " << new_light_state;
        break;
    }
}

light_states pi_pico_light_controller::set_physical_light_state(light_states new_light_state) {
    light_states ret_value;

    std::cout << __func__ << ":" << __LINE__;
    ret_value = light_state_d.light_should_be();
    std::cout << __func__ << ":" << __LINE__ << " ret_value = " << ret_value;
    switch (new_light_state) {
    case light_on:
        std::cout << __func__ << ":" << __LINE__;
        light_controller_class_object.set_physical_light_state(new_light_state);
        break;
    case light_off:
        std::cout << __func__ << ":" << __LINE__;
        light_controller_class_object.set_physical_light_state(new_light_state);
        break;
    case undefined_light_state:
        std::cout << __func__ << ":" << __LINE__;
        std::cout << "Shouldn't be trying to set light_state to undefined.";
        light_controller_class_object.set_physical_light_state(new_light_state);
        break;
    default:
        std::cout << "Confused state for light_state_d ret_value is  " << ret_value;
    }
    std::cout << __func__ << ":" << __LINE__;
    return ret_value;
}
