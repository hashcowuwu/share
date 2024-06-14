#include <stdio.h>
#include <pthread.h>

#define N 1
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int buffer_has_data = 0;


void* producer(void* arg){
    pthread_mutex_lock(&output_mutex);

    printf("<");

    pthread_mutex_unlock(&output_mutex);

    pthread_mutex_lock(&mutex);
   
    buffer_has_data = 1;

    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);

    return NULL;
    
}


void* consumer(void* arg){
    pthread_mutex_lock(&mutex);

    while(buffer_has_data == 0){
        pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_lock(&output_mutex);
    printf(">");
    pthread_mutex_unlock(&output_mutex);
    buffer_has_data = 0;

    pthread_mutex_unlock(&mutex);

    return NULL;
}


int main(){
    pthread_t pthreads[N];
    pthread_t bthreads[N];
    for (int i = 0 ; i < N ; ++ i ) {
        pthread_create(&pthreads[i],NULL,producer,0);
        pthread_create(&bthreads[i],NULL,consumer,0);
    }
    
    for (int i = 0 ; i < N ; ++ i ) {
        pthread_join(pthreads[i], NULL);
        pthread_join(bthreads[i], NULL);
    }

}
