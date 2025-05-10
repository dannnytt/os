#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define VECTOR_SIZE 100000000
#define THREADS_COUNT 12

typedef long long ll;
typedef unsigned int uint;

int vector[VECTOR_SIZE];

typedef struct {
    uint thread_id;
    ll result;
    ll start;
    ll end;
} args_t;

void fill_int(int *vector, size_t size) {
    for (size_t i = 0; i < size; i++) {
        vector[i] = rand() % size;
    }
}

void *calculate_sum(void *arg) {
    args_t *params = (args_t *)arg;
    params->result = 0;
    
    for (size_t i = params->start; i < params->end; i++) {
        params->result += vector[i];
    }

    printf("Сумма последовательности[%d] чисел на Си [thread%d] = %lld\n", 
           (params->thread_id + 1), params->thread_id, params->result);
    
    return NULL;
}

ll get_sum(args_t *params) {
    return params[0].result + params[1].result;
}

int main(int argc, char *argv[]) {
    struct timeval start_t, end_t;
    
    srand(time(NULL));
    fill_int(vector, VECTOR_SIZE);

    pthread_t threads[THREADS_COUNT];
    args_t params[THREADS_COUNT];

    for (uint i = 0; i < THREADS_COUNT; i++) {
        uint start = i * (VECTOR_SIZE / THREADS_COUNT);
        uint end = (i == THREADS_COUNT - 1) ? VECTOR_SIZE : (i + 1) * (VECTOR_SIZE / THREADS_COUNT);
        
        params[i].thread_id = i;
        params[i].start = start;
        params[i].end = end;

        pthread_create(&threads[i], NULL, calculate_sum, &params[i]);
    }

    gettimeofday(&start_t, NULL);

    for (uint i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_t, NULL);
    
    double total_t = (end_t.tv_sec - start_t.tv_sec) + 
                     (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    printf("Время выполнения  = %f секунд\n", total_t);

    printf("Сумма элементов массива: %lld\n", get_sum(params));

    return 0;
}
