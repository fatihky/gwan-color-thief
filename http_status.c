
// ./gwan -r http_status.c

#include <stdio.h>
#include "gwan.h"

int main(int argc, char *argv[])
{
  int x = 0;

  printf("Enter the status code > ");
  scanf("%d", &x);

  while(x != 0){
    printf("%s\n", http_status(x));
    printf("Enter the status code > ");
    scanf("%d", &x);
  }

  return 0;
}
