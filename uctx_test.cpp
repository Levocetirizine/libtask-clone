#include <iostream>
#include <ucontext.h>

#define F_MAX 10

using namespace std;

ucontext_t ut[3];
char stk_buf1[4096];
char stk_buf2[4096];

void f1()
{
  for (int i = 0; i < F_MAX; i++) {
    cout << "f1: " << i << endl;
    swapcontext(&ut[1], &ut[2]);
  }
}

void f2()
{
  for (int i = 0; i < F_MAX; i++) {
    cout << "f2: " << i << endl;
    swapcontext(&ut[2], &ut[1]);
  }
}

int 
main(int argc, char* argv[])
{
  cout << "start" << endl;

  getcontext(&ut[1]);
  ut[1].uc_stack.ss_sp = stk_buf1;
  ut[1].uc_stack.ss_size = sizeof(stk_buf1);
  ut[1].uc_link = &ut[2];
  makecontext(&ut[1], f1, 0);


  getcontext(&ut[2]);
  ut[2].uc_stack.ss_sp = stk_buf2;
  ut[2].uc_stack.ss_size = sizeof(stk_buf2);
  ut[2].uc_link = &ut[0];
  makecontext(&ut[2], f2, 0);

  cout << "start swap" << endl;

  swapcontext(&ut[0], &ut[1]);

  cout << "finish swap" << endl;

  return 0;
}

