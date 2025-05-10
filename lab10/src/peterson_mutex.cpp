#include "peterson_mutex.h"

peterson_mutex_t::peterson_mutex_t() {
    want[0] = want[1] = false;
    waiting = 0;
}

void peterson_mutex_t::lock(uint thread_id) {
    uint other_thread_id = 1 - thread_id;
    want[thread_id] = true;
    waiting = thread_id;

    while(want[other_thread_id] && waiting == thread_id) {
    
    }
}

void peterson_mutex_t::unlock(uint thread_id) {
    want[thread_id] = false;
}

