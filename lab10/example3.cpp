#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "peterson_mutex.h"

#define THREAD_COUNT 2

peterson_mutex_t mutex;

char sh[6];    

struct thread_data_t {
    unsigned int thread_id;
};

void* thread(void* params){
    
    thread_data_t *args = (thread_data_t*) params;
    
    int counter = 0;
    while (counter != 5) {
        
        mutex.lock(args->thread_id);
        
        if (counter % 2 == 0) {
            snprintf(sh, sizeof(sh), "Hello");
        } else {
            snprintf(sh, sizeof(sh), "Bye_u");
        }

        counter++;
        printf("thread[%d]: %s\n", args->thread_id, sh);
        
        mutex.unlock(args->thread_id);
        sleep(1);
    }

    return NULL;
}

int main( void ) {
    
    pthread_t threads[THREAD_COUNT];
    thread_data_t thread_data[THREAD_COUNT];
    
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, &thread, &thread_data[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}