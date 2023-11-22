#ifndef PWM_LIGHT_H
#define PWM_LIGHT_H

#define pwm_light_1_pin "PWM0A";
#define pwm_light_2_pin "PWM0B";

enum class e_pwm_light_id {
    e_pwm_light_1,
    e_pwm_light_2,
};

class pi_pico_pwm_light {
public:
    pi_pico_pwm_light();
    pi_pico_pwm_light(e_pwm_light_id which_pwm_light);
    ~pi_pico_pwm_light();
    void pi_pico_pwm_light_on(unsigned int brightness);
    void pi_pico_pwm_light_off(void);
    int pi_pico_pwm_light_get_brightness();
    void pi_pico_pwm_light_set_brightness(int new_brightness);
private:
    std::string pi_pico_pwm_pin;
    e_pwm_light_id pi_pico_pwm_light_id;
    int pi_pico_pwm_light_brightness;
    /* Interfaces to PWM stuff */
    // pi_pico_pwm *dc;          /* Pulse Width Modulated brightness controll for pwm_light */
};

#endif /* PWM_LIGHT_H */
