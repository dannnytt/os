#include <array>

using uint = unsigned int;

class peterson_mutex_t {

public:
    peterson_mutex_t();

public:
    void lock(uint thread_id);
    void unlock(uint thread_id);

private:
    
    // флаг заинтересованности потоков
    std::array<bool, 2> want;
    
    // идентификатор ждущего потока
    uint waiting;
};