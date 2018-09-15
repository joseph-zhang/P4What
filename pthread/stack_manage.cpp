#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#define NUM_THREAD 4
#define EXTRA_BYTE 1e6
using namespace std;

void* test (void* threadId) {
  int buffer[2][1024][1025];
  cout << "Thread #" << (long)threadId << endl;
  pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
  pthread_t threads[NUM_THREAD];
  size_t stacksize;

  // initialize attribute variable
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  // get the default stack size
  pthread_attr_getstacksize(&attr, &stacksize);
  cout << "Default stack size = " << stacksize  << " Byte"<< endl;
  cout << "i.e. " << stacksize / 1024 / 1024 << " MB" << endl;

  // The fact is that the default stacksize is 8MB,
  // but we need more.
  stacksize = sizeof(int) * 1024 * 1025 * 2;
  cout << "However we need at least " << stacksize << " Byte" << endl;

  int ret_val = 0;

  // TEST_CASE: do this, the stack error occur
  /*
  for (long i = 0; i < NUM_THREAD; i++) {
    cout << "In Main: Creating thread " << i << endl;
    ret_val = pthread_create(&threads[i], NULL, test, (void*) i);
    sleep(1);
  }
  */

  // resize the stack size
  pthread_attr_setstacksize(&attr, stacksize + EXTRA_BYTE);

  pthread_attr_getstacksize(&attr, &stacksize);
  cout << "Now the stack size is " << stacksize << " Byte" << endl;

  for (long i = 0; i < NUM_THREAD; i++) {
    cout << "In Main: Creating thread " << i << endl;
    ret_val = pthread_create(&threads[i], &attr, test, (void*) i);
    sleep(1);
  }

  pthread_exit(NULL);
}
