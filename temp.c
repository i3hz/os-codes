#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];  // Shared buffer to store items
int count = 0;  // Keeps track of the number of items in the buffer
sem_t empty;  // Semaphore to keep track of empty slots in the buffer
sem_t full;  // Semaphore to keep track of full slots in the buffer
pthread_mutex_t mutex;  // Mutex to protect access to shared resources

// Producer function to produce items and place them in the buffer
void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Generate a random item
        sem_wait(&empty);  // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex);  // Lock the mutex to access shared buffer
        buffer[count] = item;  // Place the item in the buffer
        count++;  // Increment the count
        printf("Producer produced: %d\n", item);
        pthread_mutex_unlock(&mutex);  // Unlock the mutex
        sem_post(&full);  // Signal that the buffer has a full slot
        sleep(1);  // Sleep for a short duration to simulate time taken for producing an item
    }
    return NULL;
}

// Consumer function to consume items from the buffer
void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait for a full slot in the buffer
        pthread_mutex_lock(&mutex);  // Lock the mutex to access shared buffer
        item = buffer[count - 1];  // Get the item from the buffer
        count--;  // Decrement the count
        printf("Consumer consumed: %d\n", item);
        pthread_mutex_unlock(&mutex);  // Unlock the mutex
        sem_post(&empty);  // Signal that the buffer has an empty slot
        sleep(1);  // Sleep for a short duration to simulate time taken for consuming an item
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    sem_init(&empty, 0, BUFFER_SIZE);  // Initialize empty semaphore with buffer size
    sem_init(&full, 0, 0);  // Initialize full semaphore to 0 since buffer is initially empty
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex
    pthread_create(&prod_thread, NULL, producer, NULL);  // Create the producer thread
    pthread_create(&cons_thread, NULL, consumer, NULL);  // Create the consumer thread
    pthread_join(prod_thread, NULL);  // Wait for the producer thread to finish
    pthread_join(cons_thread, NULL);  // Wait for the consumer thread to finish
    sem_destroy(&empty);  // Destroy the empty semaphore
    sem_destroy(&full);  // Destroy the full semaphore
    pthread_mutex_destroy(&mutex);  // Destroy the mutex
    return 0;
}

