//Gerardo Wibmer
#include "thread.h"

int readers = 0;
sem_t r_Lock;
sem_t w_Lock;

//purpose:Make the writer enter the critical section and read.
//Inputs: a not specified pointer
//Assumptions:none
//Post Condition:a Null pointer will be returned
void *writer(void *args) {
  printf("Writer is created..\n");
  // Request critical section
  sem_wait(&w_Lock);
  if(1)
  {
    printf("Writer is writing\n");
    printf("Writer finished writing\n");
  }
  // leave the crtitcal section
  sem_post(&w_Lock);
  return NULL;
}

//purpose: Make the reader enter critical section read and leave the critical section
//Inputs:a not specified pointer
//Assumptions:
//Post Condition:a Null pointer will be returned
void *reader(void *args) {
  printf("Reader is created..\n");
  sem_wait(&r_Lock);
  if(1)
  {
    // Increase number of readers
    readers++;
    if (readers == 1)
      // Make sure no wirter enters if there is a reader
     sem_wait(&w_Lock);
  }

  // Other readers can enter if there is a reader in the critical section
  sem_post(&r_Lock);
  // performing reading
  printf("Reader is reading\n");
  printf("Reader finished reading\n");
  sem_wait(&r_Lock);
  if(1)
  {
    // Decreasing reader count since a reader wants to leave the critical
    // section
    readers--;
    // No reader left on the critical section
    if (readers == 0)
      // writer can enter the critical section
      sem_post(&w_Lock);
  }
  // reader leaves
  sem_post(&r_Lock);
  return NULL;
}


//purpose:Go trhough the file and create the threads
//Inputs:none
//Assumptions:none
//Post Condition:0 will be return
int main() {
  sem_init(&r_Lock, 0, 1);
  sem_init(&w_Lock, 0, 1);
  pthread_t threads[10000];
  int readerID = 0, writerID = 0, i = 0;
  FILE *file = fopen("scenarios.txt", "r");
  char r_or_w;
  if (file) {
    while (fscanf(file, "%c", &r_or_w) != EOF) {
      if (r_or_w == 'r') {
        int *id = createArgs(readerID++);
        threads[i++] = createThread(reader, id);

      } else if (r_or_w == 'w') {

        int *id = createArgs(writerID++);
        threads[i++] = createThread(writer, id);
        
      }
    }
    fclose(file);

    joinThreads(threads, i);
    return 0;
  }
 return 0;

}