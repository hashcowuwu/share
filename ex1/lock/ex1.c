
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 10000000
unsigned long a = 0;

pthread_mutex_t global_lock;

void *routine(void *arg) {
  for (int i = 0 ; i < N ; ++ i) {

    pthread_mutex_lock(&global_lock);
    a ++ ;
    pthread_mutex_unlock(&global_lock);
  }
  return NULL;
}

int main() {

  pthread_mutex_init(&global_lock, NULL);
  
  pthread_t threads[2];
  for (int i =  0 ; i < 2 ; ++ i )
    pthread_create(&threads[i], NULL, routine, 0);

  for (int i = 0 ; i < 2  ; ++ i ) 
    pthread_join(threads[i],NULL);

  printf("%lu\n",a);

  return 0;
}
