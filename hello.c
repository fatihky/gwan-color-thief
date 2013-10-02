#include <stdio.h>
#include "gwan.h"

int main(int argc, char *argv[])
{
  if(argc > 0)
  {
     while(argc--) printf("argv[%d]: %s\n", argc, argv[argc - 1]);
  }
  return 0;
}
