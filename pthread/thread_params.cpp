#include <pthread.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#define NUM_THREAD 5
using namespace std;

struct thread_data {
  int thread_id;
  int sum;

  /* another choice is char*, then sprintf */
  string message;
} thread_datas[NUM_THREAD];


/* the function to be called by threads */
void* hello_message (void* threadParam) {
  struct thread_data* subdata = (struct thread_data*) threadParam;

  cout << "This is thread #" << subdata -> thread_id
       << ": " << subdata -> message << " Sum = " << subdata -> sum
       << "." << endl;
  pthread_exit(NULL);
}


int main (int argc, char* argv[]) {
  pthread_t threads[NUM_THREAD];

  int ret_val = 0;
  int sum = 0;

  for (long i = 0; i < NUM_THREAD ; i++) {
    sum += i;
    ostringstream buffer;

    /* init datas */
    thread_datas[i].thread_id = i;
    thread_datas[i].sum = sum;

    buffer << "Hello " << i << "!!" << endl;
    thread_datas[i].message = buffer.str();
    buffer.str("");

    cout << "Creating thread  " << i << endl;
    ret_val = pthread_create(&threads[i], NULL,
                             hello_message, (void*) &thread_datas[i]);
    if (ret_val) {
      cout << "ERROR!! return code of pthread_cread: " << ret_val << endl;
      exit(-1);
    }
  }
  pthread_exit(NULL);
}
