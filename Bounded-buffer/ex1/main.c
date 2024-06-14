#include <stdio.h>
#include <pthread.h>

#define N 2
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int n ;
int buffer_has_data = 0;


void* producer(void* arg){


    for (int i = 1 ; i < n; ++ i )
    printf("<");

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

    for (int i = 1 ; i < n; ++ i )
    printf(">");

    buffer_has_data = 0;

    pthread_mutex_unlock(&mutex);

    return NULL;
}


int main(){
    pthread_t pthreads[N];
    pthread_t bthreads[N];
    scanf("%d",&n);
    pthread_create(&bthreads[0],NULL,consumer,0);
    pthread_create(&pthreads[0],NULL,producer,0);
    pthread_join(pthreads[0], NULL);
    pthread_join(bthreads[0], NULL);

}
