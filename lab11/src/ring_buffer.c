#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define QUEUE_SIZE 5
#define THREAD_COUNT 2

typedef struct {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
    int count;
    sem_t full;
    sem_t empty;
    pthread_mutex_t mutex;
} ring_buffer_t;

void init_buffer(ring_buffer_t *buf) {
    buf->front = 0;
    buf->rear = 0;
    buf->count = 0;
    pthread_mutex_init(&buf->mutex, NULL);
    sem_init(&buf->empty, 0, QUEUE_SIZE); // Изначально все места свободны
    sem_init(&buf->full, 0, 0);           // Изначально очередь пустая
}

void add_elem(ring_buffer_t *buf, int elem) {
    buf->queue[buf->rear] = elem;
    buf->rear = (buf->rear + 1) % QUEUE_SIZE; 
    buf->count++;
}

int remove_elem(ring_buffer_t* buf) {
    int elem = buf->queue[buf->front];
    buf->front = (buf->front + 1) % QUEUE_SIZE;
    buf->count--;
    return elem;
}

void* producer(void* params) {
    ring_buffer_t *buf = (ring_buffer_t*) params;
    
    while (true) {
        int elem = rand() % 100;

        sem_wait(&buf->empty);

        pthread_mutex_lock(&buf->mutex);
        add_elem(buf, elem);
        printf("Производитель добавил %d в очередь.\n", elem);
        pthread_mutex_unlock(&buf->mutex);

        sem_post(&buf->full);
        sleep(1);
    }

    return NULL;
}

void* consumer(void* params) {
    ring_buffer_t *buf = (ring_buffer_t*) params;
    
    while (true) {
        
        sem_wait(&buf->full);

        pthread_mutex_lock(&buf->mutex);
        int elem = remove_elem(buf);
        printf("Потребитель забрал %d из очереди.\n", elem);
        pthread_mutex_unlock(&buf->mutex);

        sem_post(&buf->empty);
        sleep(2);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    ring_buffer_t buffer;
    init_buffer(&buffer);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, &buffer);
    pthread_create(&consumer_thread, NULL, consumer, &buffer);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&buffer.mutex);
    sem_destroy(&buffer.empty);
    sem_destroy(&buffer.full);

    return 0;
}
