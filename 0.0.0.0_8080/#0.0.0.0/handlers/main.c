#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "gwan.h"

int init(int argc, char *argv[])
{

  u32 *entity_size_limit = (u32*)get_env(argv, MAX_ENTITY_SIZE);
  *entity_size_limit = 20 * 1024 * 1024; // 20 MiB

//  u32 *states = (u32 *)get_env(argv, US_HANDLER_STATES);
//  *states =   (1L << HDL_AFTER_READ) 
//            | (1L << HDL_AFTER_PARSE);

  return 0;
}

void clean(int argc, char *argv[])
{
}

int main(int argc, char *argv[])
{
  long state = (long)argv[0];

  switch(state)
  {

    case HDL_AFTER_READ:
    {

//      char *req = (char*)get_env(argv, REQUEST);
//      printf("Request: %s\n", req);

    } break;

    case HDL_AFTER_PARSE:
    {

    } break;

    default:
    {

    } break;

  }
  return 255;
}

