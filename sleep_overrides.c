#include <unistd.h>
#include "pico/time.h"

int usleep(useconds_t usec) {
    sleep_us(usec);
    return 1;
}

unsigned int sleep(unsigned int seconds) {
    return usleep(seconds * 1000000);
}

