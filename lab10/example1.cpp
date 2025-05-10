#include <iostream>
#include <thread> 
#include <vector>
#include <array>
#include <sys/time.h>

#include "peterson_mutex.h"

#define VECTOR_SIZE 100000000
#define THREADS_COUNT 2

using ll = long long;
using uint = unsigned int;

std::vector<int> vector(VECTOR_SIZE);

peterson_mutex_t peterson_mutex;

struct args_t {
    uint thread_id;
    ll result;
    ll start;
    ll end;

    args_t() : thread_id(0), start(0), end(0) {}
    
    args_t(uint id, uint start_point, uint end_point) : thread_id(id), 
                                                        start(start_point), 
                                                        end(end_point) 
    {}
    
};

void fill_int(std::vector<int> &vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        vector[i] = rand() % (vector.size());
    }
}

void calculate_sum(args_t &params) {
    params.result = 0;
    
    peterson_mutex.lock(params.thread_id);
    
    for (size_t i = params.start; i < params.end; i++) {
        params.result += vector[i];
    }
    
    peterson_mutex.unlock(params.thread_id);
    
    printf("Сумма последовательности[%d] чисел на си++ [thread%d] = %lld\n", 
                    (params.thread_id + 1), params.thread_id, params.result);
}

ll get_sum(std::array<args_t, THREADS_COUNT> &array) {
    return array[0].result + array[1].result;
}

int main(int argc, char *argv[]) {
    
    srand(time(nullptr));
    fill_int(vector);

    std::array<std::thread, THREADS_COUNT> threads;
    std::array<args_t, THREADS_COUNT> params;
    std::array<ll, THREADS_COUNT> results;

    for (uint i = 0; i < THREADS_COUNT; i++) {
        uint id = i;
        uint start = i * (VECTOR_SIZE / THREADS_COUNT);
        uint end = (i == THREADS_COUNT - 1) ? VECTOR_SIZE : (i + 1) * (VECTOR_SIZE / THREADS_COUNT);

        
        params[i] = args_t(id, start, end);
        threads[i] = std::thread(calculate_sum, std::ref(params[i]));
    }

    for (uint i = 0; i < THREADS_COUNT; i++) {
        threads[i].join();
    }

    std::cout << "Сумма элементов массива: " << get_sum(params) << std::endl;

    return 0;
}