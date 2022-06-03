#include <stdio.h>
#include <unistd.h>

void processus1()
{
  for (int i = 0;; i++)
  {
    printf("Hello, world from P1: i=%d\n", i);
    // schedule();
  }
}
