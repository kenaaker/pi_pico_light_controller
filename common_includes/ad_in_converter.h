#ifndef AD_CONVERTER_H
#define AD_CONVERTER_H
#include <unistd.h>
#include <stdio.h>
#include <string>

class ad_in_converter {
  public:
    ad_in_converter(int ain_channel = 0);
    ~ad_in_converter(void);
    uint16_t converter_read();
    void set_ain_channel(int in_channel);
    void set_lower_bound(int new_lower_bound);
    void set_upper_bound(int new_upper_bound);
    void set_under_voltage_value(int new_under_voltage_value);
    void set_under_voltage_callback(void (*new_under_voltage_callback)(int new_voltage));
    void set_instrument_name(std::string instr_name);
    const std::string get_instrument_name(void);
  private:
    std::string instrument_name;
    int under_voltage_value;
    void (* under_voltage_callback)(int new_voltage);
    int lower_bound;
    int upper_bound;
    int ad_device_in_channel;
    int last_ranged_value;
    bool adc_init_done = false;
};

#endif // AD_CONVERTER_H
