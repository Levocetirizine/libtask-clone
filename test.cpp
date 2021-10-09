#include <iostream>
#include "task.h"

static constexpr int F1_MAX = 10;
static constexpr int F2_MAX = 6;
static constexpr int F3_MAX = 100;
static constexpr int STK_SIZE = 32768;

using namespace std;

void f1(void *arg)
{
  for (int i = 0; i < F1_MAX; i++) {
    cout << "f1: " << i << endl;
    taskyield();
  }
}

void f2(void *arg)
{
  for (int i = 0; i < F2_MAX; i++) {
    cout << "f2: " << i << endl;
    taskyield();
  }
}

void f3(void *arg)
{
  tasksystem();
  for (int i = 0; i < F3_MAX; i++) {
    cout << "f3: " << i << endl;
    taskyield();
  }
}

void taskmain(int argc, char *argv[])
{
  taskcreate(f1, NULL, STK_SIZE);
  taskcreate(f2, NULL, STK_SIZE);
  taskcreate(f3, NULL, STK_SIZE);
}