#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <thread>
#include <queue>
#include <string>


typedef struct timer_event {
    std::chrono::milliseconds event_time;
    bool (*timer_callback)(std::chrono::milliseconds time_something_happens);
} timer_event_t;

class timer_comparison {
public:
    bool operator() (const timer_event_t left_hand_side, const timer_event_t &right_hand_side) const {
        bool ret_value;

        ret_value = (left_hand_side.event_time > right_hand_side.event_time);
        return ret_value;
    }
};

typedef std::priority_queue<timer_event_t, std::vector<timer_event_t>, timer_comparison> timer_queue_type;

class timer {
public:
    timer(void);
    timer(std::string);
    ~timer(void);

    void add_callback(bool (* new_callback)(std::chrono::milliseconds), std::chrono::milliseconds parm_go_off_time);

    void exec(void);

 private:
    bool (* callback)(timer_event_t);
    std::string timer_name;
};

#endif // TIMER_H
