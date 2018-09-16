#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void* func (void*){
}

int main (int argc, char* argv[]) {
  pthread_t thread;
  int ret_val = 0;
  long i = 0;

  while (true) {
    ret_val = pthread_create(&thread, NULL, func, NULL);
    if (ret_val) {
      cout << "ERROR!! return code of pthread_create(): " << ret_val << endl;
      exit(-1);
    }
    cout << "i = " << ++i << endl;
  }
  pthread_exit(NULL);
}
