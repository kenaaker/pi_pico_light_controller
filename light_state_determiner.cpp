
#include <stdint.h>
#define _POSIX_TIMERS 1
#define _POSIX_MONOTONIC_CLOCK 1
#include <time.h>

#include "light_state_determiner.h"

static timespec failed_timespec = {
    -1,                                     /* With the GNU extensions, this would be tv_secs */
    -1                                      /* With the GNU extensions, this would be tv_nsecs */
};

static milli_timespec_t successful_milliseconds_timespec;

static milli_timespec_t milliseconds_timespec_from_timespec(timespec parm_time_spec) {
    milli_timespec_t local_milli_time_spec;

    local_milli_time_spec.tv_seconds = parm_time_spec.tv_sec;
    local_milli_time_spec.tv_milliseconds = parm_time_spec.tv_nsec / 1000000;
    return local_milli_time_spec;
}

static milli_timespec_t timespec_to_milliseconds(timespec &parm_time_spec) {
    milli_timespec_t local_milli_time_spec;

    local_milli_time_spec.tv_seconds = parm_time_spec.tv_sec;
    local_milli_time_spec.tv_milliseconds = parm_time_spec.tv_nsec / 1000 / 1000;

    successful_milliseconds_timespec = local_milli_time_spec;
    return successful_milliseconds_timespec
            ;
}

static void adjust_milliseconds_timespec(milli_timespec_t &parm_invalid_milli_timespec) {
    while (parm_invalid_milli_timespec.tv_milliseconds > 1000) {
        /* We've overflowed the milliseconds value, subtract 1000 from milliseconds and add a second */
        parm_invalid_milli_timespec.tv_milliseconds -= 1000;
        parm_invalid_milli_timespec.tv_seconds += 1;
    }
}

static milli_timespec_t make_timeout_time(timespec parm_timespec, int64_t timeout_in_milliseconds) {
    static timespec local_timespec;
    milli_timespec_t local_milli_time_spec;

    local_milli_time_spec.tv_seconds = parm_timespec.tv_sec;
    local_milli_time_spec.tv_milliseconds = parm_timespec.tv_nsec / 1000 / 1000;
    local_milli_time_spec.tv_milliseconds += timeout_in_milliseconds;
    adjust_milliseconds_timespec(local_milli_time_spec);
    successful_milliseconds_timespec = local_milli_time_spec;

    return successful_milliseconds_timespec;
}

static timespec get_local_timespec(void) {
    timespec local_timespec;
    int local_get_time_rc;

    local_get_time_rc = clock_gettime(CLOCK_MONOTONIC, &local_timespec);
    if (local_get_time_rc < 0) {
        return failed_timespec;
    } else {
       return local_timespec;
    }
}

static int64_t get_local_time_in_milliseconds(void) {
    int64_t local_time_in_milliseconds;
    int local_timespec_rc;
    timespec local_timespec;

    local_timespec_rc = clock_gettime(CLOCK_MONOTONIC, &local_timespec);

    return local_time_in_milliseconds;
}

light_state_determiner::light_state_determiner() {

    struct timespec local_time_spec;
    int local_clock_gettime_rc;

    light_intensity_value = 0;
    local_clock_gettime_rc = clock_gettime(CLOCK_MONOTONIC, &local_time_spec);           /* Start with sense having never fired */
#if 0
    occupancy_timeout (last_time_occupancy_sensor_fired, 5*1000);/* Use 5 minutes as timeout value default */
#endif
    user_light_setting = undefined_light_state;
}

void light_state_determiner::set_light_intensity(unsigned int light_in) {
    light_intensity_value = light_in;
}

int64_t light_state_determiner::light_intensity(void) {
    return light_intensity_value;
}

void light_state_determiner::occupancy_sensor_fired(void) {
    last_time_occupancy_sensor_fired = milliseconds_timespec_from_timespec(get_local_timespec());
}

#if 0
timespec_t light_state_determiner::last_occupancy_detected(void) {
    return last_time_occupancy_sensor_fired;
}
#endif

void light_state_determiner::occupancy_detected(void) {
    occupancy_sensor_fired();
}

void light_state_determiner::set_occupancy_timeout(int64_t timeout_value) {
    occupancy_timeout = make_timeout_time(get_local_timespec(), timeout_value);
}

light_states light_state_determiner::light_should_be(void) {
    light_states ret_value;

    if (user_light_setting == light_on) {
        ret_value = light_on;
    } else if (user_light_setting == light_off) {
        ret_value = light_off;
    } else { /* The user hasn't done anything particular yet, undefined state */
        int64_t occupancy_timeout;
        timespec local_time_spec;
        unsigned int seconds_to_timeout;

        occupancy_timeout = last_occupancy_detected();
        if (occupancy_timeout < clock_gettime(CLOCK_MONOTONIC, &local_time_spec)) {
            ret_value = light_off;
        } else {
            /* Now check the light intensity to see if we should turn the light on. */
            if (light_intensity_value < turn_on_low_bound) {
                ret_value = light_on;
            } else {
                if (light_intensity_value > turn_off_high_bound) {
                    ret_value = light_off;
                } else {
                    ret_value = light_on;
                }
            }
        }
    }
    return ret_value;
}

light_states light_state_determiner::user_set_light_state(void) {
    return user_light_setting;
}

void light_state_determiner::user_set_light_off(void) {
    user_light_setting = light_off;
}

void light_state_determiner::user_set_light_on(void) {
    user_light_setting = light_on;
}

void light_state_determiner::user_set_light_to_default(void) {
    user_light_setting = undefined_light_state;
}

void light_state_determiner::set_turn_on_low_bound(unsigned int new_low_bound) {
    turn_on_low_bound = new_low_bound;
}

void light_state_determiner::set_turn_off_high_bound(unsigned int new_high_bound) {
    turn_off_high_bound = new_high_bound;
}
