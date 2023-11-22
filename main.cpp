#include <chrono>
#include <thread>
#include <queue>
#include <iostream>
#include <stdio.h>

#include "pi_pico_light_controller.h"
#include "timer.h"

#include "pico/stdlib.h"

int main(int argc, char *argv[]) {

    timer local_timer;

    stdio_usb_init();
    /* Don't understand this at all, it seems to need 3 "sleep_for"s before output begins to be delivered to the USB thingy. ??? */


    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Running led light app." << std::endl;
    local_timer.exec();
    std::cout << "Exit led light app." << std::endl;
    return -1;
}
