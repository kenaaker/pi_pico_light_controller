#ifndef LIGHT_STATE_DETERMINER_H
#define LIGHT_STATE_DETERMINER_H

#include "light_controller_object.h"

#define _POSIX_TIMERS 1
#define _POSIX_MONOTONIC_CLOCK 1
#include <time.h>

typedef struct _milli_timespec {
    time_t tv_seconds;
    long tv_milliseconds;
} milli_timespec_t;

class light_state_determiner {
  public:
    light_state_determiner();
    void set_light_intensity(unsigned int light_in);
    int64_t light_intensity(void);
    void set_turn_on_low_bound(unsigned int new_low_bound);
    void set_turn_off_high_bound(unsigned int new_high_bound);
    void occupancy_sensor_fired(void);
    int64_t last_occupancy_detected(void);
    void occupancy_detected(void);
    void set_occupancy_timeout(int64_t timeout_value);
    light_states light_should_be(void);
    void user_set_light_off(void);
    void user_set_light_on(void);
    void user_set_light_to_default(void);
    light_states user_set_light_state(void);
  private:
    unsigned int light_intensity_value;
    milli_timespec_t last_time_occupancy_sensor_fired;
    milli_timespec_t occupancy_timeout;
    enum light_states user_light_setting;
    unsigned int turn_on_low_bound;
    unsigned int turn_off_high_bound;
};

#endif // LIGHT_STATE_DETERMINER_H
