#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


int count = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
  while(1) {
    sem_wait(&empty);
    printf("<");
    sem_post(&full);
  }
  return NULL;
}


void* consumer(void* arg) {
  while(1) {
    sem_wait(&full);
    printf(">");
    sem_post(&empty);
  }
  return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    // 初始化信号量
    sem_init(&empty, 0, 1); // 初始空位数为缓冲区大小
    sem_init(&full, 0, 0); // 初始满位数为0
    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    // 销毁信号量和互斥锁
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
