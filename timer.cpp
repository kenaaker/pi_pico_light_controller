#include <chrono>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <queue>

#include "timer.h"

typedef std::priority_queue<timer_event_t, std::vector<timer_event_t>, timer_comparison> timer_queue_type;
timer_queue_type timer_queue;

void timer::add_callback(bool (* new_callback)(std::chrono::milliseconds parm_when_timer_went_off), std::chrono::milliseconds parm_go_off_time) {
    timer_event_t local_timer_event;

    local_timer_event.event_time = parm_go_off_time;
    local_timer_event.timer_callback = new_callback;
    timer_queue.push(local_timer_event);
}

void timer::exec(void) {
    using namespace std::chrono;
    int loop_count;

    while (true) {
        timer_event_t local_timer_event;

        if (timer_queue.empty()) {
            std::cout << __func__ << ":" << __LINE__<< " timer queue for " << timer_name << " is empty." << std::endl;
            break;
        } else {
            local_timer_event = timer_queue.top();
            timer_queue.pop();
            std::this_thread::sleep_for(local_timer_event.event_time);
            if (local_timer_event.timer_callback != nullptr) {
                bool callback_result;
                callback_result = local_timer_event.timer_callback(local_timer_event.event_time);
                if (callback_result) {
                    add_callback(local_timer_event.timer_callback, local_timer_event.event_time);
                }
            }
            ++loop_count;
        } /* endif */
    } /* end while */
    return;
}

timer::timer(void) {
    timer_name = "foo timer name";
}

timer::timer(std::string a_timer_name) {
    timer_name = a_timer_name;
}

timer::~timer(void) {
    ;
}
