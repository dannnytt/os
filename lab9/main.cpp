#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 2

pthread_spinlock_t lock;
char sh[6];    

struct thread_data_t {
    u_int thread_id;
};

void* thread(void* params){
    
    thread_data_t *args = (thread_data_t*) params;
    
    int counter = 0;
    while (1) {
        
        pthread_spin_lock(&lock);
        
        if (counter % 2 == 0) {
            snprintf(sh, sizeof(sh), "Hello");
        } else {
            snprintf(sh, sizeof(sh), "Bye_u");
        }

        counter++;
        printf("thread[%d]: %s\n", args->thread_id, sh);
        
        pthread_spin_unlock(&lock);
        sleep(1);
    }

    return NULL;
}

int main( void ) {
    
    pthread_spin_init(&lock, 0);
    
    pthread_t threads[THREAD_COUNT];
    thread_data_t thread_data[THREAD_COUNT];
    
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_data[i].thread_id = (i + 1);
        pthread_create(&threads[i], NULL, &thread, &thread_data[i]);
    }

    while (1) {
        pthread_spin_lock(&lock);
        printf("thread[main]: %s\n", sh);
        pthread_spin_unlock(&lock);
        sleep(1);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_spin_destroy(&lock);
    return 0;
}