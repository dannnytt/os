#include "modified_peterson_mutex.h"

modified_peterson_mutex_t::modified_peterson_mutex_t() {
    want[0].store(false);
    want[1].store(false);
    waiting.store(0);
}

void modified_peterson_mutex_t::lock(uint thread_id) {
    uint other_thread_id = 1 - thread_id;
    want[thread_id].store(true);
    waiting.store(thread_id);

    while(want[other_thread_id].load() && waiting.load() == thread_id) {
    
    }
}

void modified_peterson_mutex_t::unlock(uint thread_id) {
    want[thread_id].store(false);
}

