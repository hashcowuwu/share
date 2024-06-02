#include <stdio.h>
#include <pthread.h>

#define N 10000000
unsigned long a = 0;


void *routine(void *arg) {
  for (int i = 0 ; i <= N ; ++ i) a ++ ;
  return NULL;
}

int main() {

}
