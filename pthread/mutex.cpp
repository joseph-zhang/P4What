#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREAD 4
using namespace std;
/* In this file, mutex protect the shared data. */
/* some related functions:

   pthread_mutex_init
   pthread_mutex_lock
   pthread_mutex_trylock
   pthread_mutex_unlock
   pthread_mutex_destroy

 */

const int VEC_LEN = 1e5;

typedef struct {
  double* xs;
  double* ys;
  double sum;
  int vec_length;
}Dot;

/* Define globally accessible variables and a mutex variable */
Dot dots;
pthread_mutex_t mutexsum;

void* calcDotProd(void* threadId) {
  long offset = (long)threadId;

  int begin = offset * dots.vec_length;
  int end = begin + dots.vec_length;

  double tempSum = 0.;
  for (int i = begin; i < end; i++)
    tempSum += (dots.xs[i] * dots.ys[i]);

  /* when overwrite, add mutex lock */
  pthread_mutex_lock(&mutexsum);
  dots.sum += tempSum;
  cout << "Thread #" << offset << " did " << begin << " to "
       << end << ": tempSum = " << tempSum <<", globalSum = "
       << dots.sum << endl;
  pthread_mutex_unlock(&mutexsum);
  pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
  pthread_attr_t attr;
  pthread_t threads[NUM_THREAD];

  /* use malloc to acquire a block of space for storing dot data */
  double* a = (double*)malloc(NUM_THREAD * VEC_LEN * sizeof(double));
  double* b = (double*)malloc(NUM_THREAD * VEC_LEN * sizeof(double));

  /* initialize the dot data */
  for (int i = 0; i < VEC_LEN * NUM_THREAD; i++) {
    *(a + i) = 1 + i;
    *(b + i) = *(a + i);
  }

  dots.xs = a;
  dots.ys = b;
  dots.vec_length = VEC_LEN;
  dots.sum = 0;

  /* initialize mutex variable */
  pthread_mutex_init(&mutexsum, NULL);

  /* initialize pthread attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (long i = 0; i < NUM_THREAD; i++)
    pthread_create(&threads[i], &attr, calcDotProd, (void*) i);

  // de-initialize the attribute information
  pthread_attr_destroy(&attr);

  void* status;
  for (long i = 0; i < NUM_THREAD; i++)
    pthread_join(threads[i], &status);

  cout << "result: dots.Sum = " << dots.sum << endl;

  /* remember to free the space we acquired */
  free(a);
  free(b);

  /* destroy the mutex */
  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
}
