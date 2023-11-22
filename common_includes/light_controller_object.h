#ifndef LIGHT_CONTROLLER_OBJECT_H
#define LIGHT_CONTROLLER_OBJECT_H

#include <iostream>

typedef enum light_states {
    light_off,
    light_on,
    undefined_light_state,
    invalid_light_state = 150
} light_states_enum_t;

#define MIN_LIGHT_INTENSITY (0)
#define MAX_LIGHT_INTENSITY (100)
#define INVALID_LIGHT_INTENSITY (MAX_LIGHT_INTENSITY + 1)

#define MIN_POWER_SUPPLY_VOLTAGE (0)
#define MAX_POWER_SUPPLY_VOLTAGE (15)
#define INVALID_POWER_SUPPLY_VOLTAGE (MAX_POWER_SUPPLY_VOLTAGE + 1)

#define MIN_DIMMER_SETTING (0)
#define MAX_DIMMER_SETTING (100)
#define INVALID_DIMMER_SETTING (MAX_DIMMER_SETTING + 1)

#define INVALID_PIR_DETECTED_PRESENCE (false)

#define MIN_PHYSICAL_LIGHT_STATE (light_off)
#define MAX_PHYSICAL_LIGHT_STATE (light_on)
#define INVALID_PHYSICAL_LIGHT_STATE_SETTING (undefined_light_state)

#define MIN_USER_SET_LIGHT_STATE (light_off)
#define MAX_USER_SET_LIGHT_STATE (light_on)
#define INVALID_USER_SET_LIGHT_STATE_SETTING (undefined_light_state)

class light_controller_object {
  public:
    typedef struct light_controller_values {
        unsigned int light_intensity;
        unsigned int power_supply_voltage;
        unsigned int dimmer_setting;
        light_states_enum_t physical_light_state;
        light_states_enum_t user_set_light_state;
        bool PIR_detected_presence;
    } light_controller_values_t;
    light_controller_object();

    unsigned int get_light_intensity(void) {
        return light_controller_values.light_intensity;
    }
    unsigned int set_light_intensity(unsigned int new_value) {
        unsigned int ret_value;
        if (new_value <= MAX_LIGHT_INTENSITY) {
            ret_value = light_controller_values.light_intensity;
            light_controller_values.light_intensity = new_value;
        } else {
            ret_value = INVALID_LIGHT_INTENSITY;
        }
        return ret_value;
    }
    unsigned int get_power_supply_voltage(void) {
        return light_controller_values.power_supply_voltage;
    }
    unsigned int set_power_supply_voltage(unsigned int new_value) {
        unsigned int ret_value;
        if (new_value <= MAX_POWER_SUPPLY_VOLTAGE) {
            ret_value = light_controller_values.power_supply_voltage;
            light_controller_values.power_supply_voltage = new_value;
        } else {
            ret_value = INVALID_POWER_SUPPLY_VOLTAGE;
        }
        return ret_value;
    }
    unsigned int get_dimmer_setting(void) {
        return light_controller_values.dimmer_setting;
    }
    unsigned int set_dimmer_setting(unsigned int new_value) {
        unsigned int ret_value;
        if (new_value <= MAX_DIMMER_SETTING) {
            ret_value = light_controller_values.dimmer_setting;
            light_controller_values.dimmer_setting = new_value;
        } else {
            ret_value = INVALID_DIMMER_SETTING;
        }
        return ret_value;
    }
    unsigned int get_PIR_detected_presence(void) {
        return light_controller_values.PIR_detected_presence;
    }
    bool set_PIR_detected_presence(bool new_value) {
        bool ret_value;
        if ((new_value == true) ||
            (new_value == false)) {
            ret_value = light_controller_values.PIR_detected_presence;
            light_controller_values.PIR_detected_presence = new_value;
        } else {
            ret_value = INVALID_PIR_DETECTED_PRESENCE;
        }
        return ret_value;
    }
    light_states_enum_t get_physical_light_state(void) {
        return light_controller_values.physical_light_state;
    }
    light_states_enum_t set_physical_light_state(light_states_enum_t new_value) {
        light_states_enum_t ret_value;
        if ((new_value >= MIN_PHYSICAL_LIGHT_STATE) &&
            (new_value <= MAX_PHYSICAL_LIGHT_STATE)) {
            ret_value = light_controller_values.physical_light_state;
            light_controller_values.physical_light_state = new_value;
        } else {
            ret_value = INVALID_PHYSICAL_LIGHT_STATE_SETTING;
        }
        return ret_value;
    }
    light_states_enum_t get_user_set_light_state(void) {
        return light_controller_values.user_set_light_state;
    }
    light_states_enum_t set_user_set_light_state(light_states_enum_t new_value) {
        light_states_enum_t ret_value;

        std::cout << __func__ << ":" << __LINE__;
        if ((new_value >= MIN_USER_SET_LIGHT_STATE) &&
            (new_value <= MAX_USER_SET_LIGHT_STATE)) {
            ret_value = light_controller_values.user_set_light_state;
            light_controller_values.user_set_light_state = new_value;
            std::cout << __func__ << ":" << __LINE__;
            set_physical_light_state(new_value);
            std::cout << __func__ << ":" << __LINE__;
        } else {
            ret_value = INVALID_USER_SET_LIGHT_STATE_SETTING;
        }
        return ret_value;
    }
    light_controller_values_t get_values() {
        light_controller_values_t local_values;

        local_values = light_controller_values;
        return local_values;
    }

  private:
    light_controller_values_t light_controller_values;

  public:

};
#endif // LIGHT_CONTROLLER_OBJECT_H
