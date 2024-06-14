#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define N 2
#define SLEEP 1
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int fish = 0;

void wait(int num) {
  int kkk = 0;
  for (int i = 1 ; i <= num ; ++ i ) {
    for (int j = 1 ; j <= num ; ++j) {
      kkk += i - j;
    }
  }
}

void* T_1(void* arg){
  while(true){
    pthread_mutex_lock(&mutex);
    while(fish != 0){
      pthread_cond_wait(&cond, &mutex);
    }
    wait(1e3);
    printf("<");
    fish ++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

  }
  return NULL;
}

void* T_2(void* arg){
  while(true){
    pthread_mutex_lock(&mutex);
    while(fish == 0){
      pthread_cond_wait(&cond, &mutex);
    }
    wait(1e3);
    printf(">");
    fish --;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void create_t(pthread_t* t){
   pthread_create(&t[0],NULL,T_1,0);
   pthread_create(&t[1],NULL,T_2,0);
}

void join_t(pthread_t* t){
  pthread_join(t[0],NULL);
  pthread_join(t[1],NULL);
}

int main() {
  pthread_t threads[N];
  create_t(threads);
  join_t(threads);
  return 0;
}
