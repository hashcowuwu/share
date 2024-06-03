#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *outputB(void *arg ){
    puts("B");
    return NULL;
}
void *outputA(void *arg){
    puts("A");
    return NULL;
}

int main() {
    pthread_t threads[2];

    while(1)
    {
        pthread_create(&threads[0],NULL,outputA,0);
        pthread_create(&threads[1],NULL,outputB,0);

        pthread_join(threads[0],NULL);
        pthread_join(threads[1],NULL);


        sleep(1);
    }

    return 0;
}
