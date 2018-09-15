#include <pthread.h>
#include <iostream>
#include <cmath>
#define NUM_THREAD 5
using namespace std;

void* calc (void* threadparam) {
  double result = 0.0;
  long thread_id = (long) threadparam;

  cout << "Thread " << thread_id << " starting.." << endl;

  // a hard work, it will cost some time to do calculation
  for (int i = 0; i < 1e6; i++) 
    result += sin(i) + cos(i);

  cout << "Thread " << thread_id << " done. "
       << "Result = " << result << endl;

  pthread_exit((void*) threadparam);
}

int main (int argc, char* argv[]) {
  pthread_t threads[NUM_THREAD];

  //declare a pthread attribute variable of the pthread_attr_t type
  pthread_attr_t attr;

  // initialize the attribute variable
  pthread_attr_init(&attr);

  // set the attribute detached status : joinable
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // the point variable, as the param of pthread_join method
  void* status;

  // the variable to restore the return status
  long ret_val = 0;

  for (long i = 0; i < NUM_THREAD; i++) {
    cout << "In Main: Creating thread " << i << endl;
    ret_val = pthread_create(&threads[i], &attr, calc, (void*) i);

    if (ret_val) {
      cout << "ERROR!! return code of pthread_create(): " << ret_val << endl;
      exit(-1);
    }
  }

  // free attribute, de-initialize
  pthread_attr_destroy(&attr);

  // wait for the other threads.
  // if joinable threads are not joined, the system resouce will not be freed timely.
  // tag :: int pthread_join(pthread_t threadid, void **value_ptr)
  for (int i = 0;i < NUM_THREAD ; i++) {
    ret_val = pthread_join(threads[i], &status);
    if (ret_val) {
      cout << "ERROR!! return code from pthread_join(): " << ret_val << endl;
      exit(-1);
    }
    cout << "In Main: join with thread " << i << " completed." << " Return status of joined thread: " << (long) status << endl;
  }

  cout << "Main completed." << endl;
  pthread_exit(NULL);
}
