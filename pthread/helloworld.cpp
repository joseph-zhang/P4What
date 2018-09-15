#include <pthread.h>
#include <iostream>
#define NUM_THREADS 5
using namespace std;

/* The function to be called by threads */
void* hello (void* threadId) {
  long tid = (long) threadId;
  cout << "Hello word! This is thread #" << tid << endl;
  pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
  /* pthread_t type contains thread Id */
  pthread_t threads[NUM_THREADS];
  int ret_val = 0;

  for (long i = 0; i < NUM_THREADS; i++) {
    cout << "In main : creating thread " << i << endl;

    /* use pthread_create to create a new thread */
    /* int pthread_create (pthread_t *thread,pthread_attr_t *attr,
                           void *(*start_routine)(void *),void *arg)
    */
    ret_val = pthread_create(&threads[i], NULL, hello, (void*)i);

    if (ret_val) {
      cout << "ERROR!! return code " << ret_val << endl;
      exit(-1);
    }
  }

  /* wait threads end */
  pthread_exit(NULL);
}
