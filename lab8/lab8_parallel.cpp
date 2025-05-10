#include <iostream>
#include <thread> 
#include <vector>
#include <array>
#include <sys/time.h>

#define VECTOR_SIZE 100000000
#define THREADS_COUNT 12

using ll = long long;
using uint = unsigned int;

std::vector<int> vector(VECTOR_SIZE);

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
    
    for (size_t i = params.start; i < params.end; i++) {
        params.result += vector[i];
    }
    
    printf("Сумма последовательности[%d] чисел на си++ [thread%d] = %lld\n", 
                    (params.thread_id + 1), params.thread_id, params.result);
}

ll get_sum(std::array<args_t, THREADS_COUNT> &array) {
    return array[0].result + array[1].result;
}

int main(int argc, char *argv[]) {
    struct timeval start_t, end_t;
    
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

    gettimeofday(&start_t, NULL);

    for (uint i = 0; i < THREADS_COUNT; i++) {
        threads[i].join();
    }

    gettimeofday(&end_t, NULL);
    
    double total_t = (end_t.tv_sec - start_t.tv_sec) + 
                     (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    printf("Время выполнения  = %f секунд\n", total_t);

    std::cout << "Сумма элементов массива: " << get_sum(params) << std::endl;

    return 0;
}