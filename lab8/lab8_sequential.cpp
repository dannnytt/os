#include <iostream>
#include <thread> // плюсовая библиотека
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>


#define VECTOR_SIZE 100000000
#define DELAY 1000 // 1 миллисекунда = 1000 микросекунд

using ll = long long;

struct args_t {
    unsigned int thread_id;
    std::vector<ll> vector;
    ll *result;
};


void fill_int(args_t &args) {
    for (size_t i = 0; i < args.vector.size(); i++) {
        args.vector[i] = rand() % (args.vector.size());
    }
}

void calculate_sum(args_t &args) {
    *args.result = 0;
    for (size_t i = 0; i < args.vector.size(); i++) {
        *(args.result) += args.vector[i];
    }
    printf("Сумма последовательности чисел на си++ [thread%d] = %lld\n", 
                            args.thread_id, *(args.result));
}

int main (void) {
    srand(time(NULL));
    struct timeval start_t, end_t;
    
    args_t args1;
    args1.thread_id = 1;
    args1.vector.resize(VECTOR_SIZE);
    args1.result = new ll;

    fill_int(args1);

    gettimeofday(&start_t, NULL);
    calculate_sum(args1);
    gettimeofday(&end_t, NULL);

    double total_t = (end_t.tv_sec - start_t.tv_sec) + 
                     (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    printf("Время выполнения  = %f секунд\n\n", total_t);
    delete args1.result;

    return 0;
}