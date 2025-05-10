#include <array>
#include <atomic>
#include <thread>

using uint = unsigned int;

class modified_peterson_mutex_t {

public:
    modified_peterson_mutex_t();

public:
    void lock(uint thread_id);
    void unlock(uint thread_id);

private:  

    // флаг заинтересованности потоков
    std::array<std::atomic<bool>, 2> want;

    // идентификатор ждущего потока
    std::atomic<uint> waiting;
};
