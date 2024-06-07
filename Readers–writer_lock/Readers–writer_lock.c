#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define the number of reader and writer threads
#define NUM_READERS 3
#define NUM_WRITERS 1

// Declare the read-write lock and the shared data
pthread_rwlock_t rwlock;
int shared_data = 0;

// Reader thread function
void *reader(void *arg) {
    int reader_id = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_rwlock_rdlock(&rwlock); // Acquire read lock
        printf("Reader %d: read shared_data = %d\n", reader_id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Release read lock
        usleep(100000); // Simulate some work (100 ms)
    }
    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int writer_id = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_rwlock_wrlock(&rwlock); // Acquire write lock
        int old_data = shared_data;
        shared_data = old_data + 1;
        printf("Writer %d: wrote shared_data = %d\n", writer_id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Release write lock
        usleep(200000); // Simulate some work (200 ms)
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize the read-write lock
    if (pthread_rwlock_init(&rwlock, NULL) != 0) {
        perror("Failed to initialize rwlock");
        exit(EXIT_FAILURE);
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy the read-write lock
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
