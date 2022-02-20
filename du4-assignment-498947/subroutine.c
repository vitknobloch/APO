/* Implementation of the subroutine subroutine_fnc */

#include "subroutine.h"

#include <unistd.h>

int subroutine_fnc(int file_descriptor)
{
  char c;
  int ret = read(file_descriptor, &c, 1);

  if (ret < 0)
    return -1;
  if (ret == 0)
    return 0;

  return c;
}
