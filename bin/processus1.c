#include <stdio.h>
#include <n7OS/process.h>

void processus1()
{
  for (int i = 0; i < 2; i++)
  {
    printf("Hello, world from P1, i=%d\n", i);
    scheduler();
  }
  terminer();
}
