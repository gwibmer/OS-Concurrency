//Gerardo Wibmer
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define Thread pthread_t
#define exitThreads() pthread_exit(NULL)
#define newInt(n) (int *)malloc(sizeof(int) * n)
#define joinThread(thread) pthread_join(thread, NULL)
int *createArgs(int i) {
  int *args = newInt(1);
  args[0] = i;
  return args;
}
Thread createThread(void *threadFunction, void *args) {
  Thread thread;
  pthread_create(&thread, NULL, threadFunction, args);
  return thread;
}
void joinThreads(pthread_t *threads, int count) {
  int i;
  for (i = 0; i < count; i++)
    joinThread(threads[i]);
}