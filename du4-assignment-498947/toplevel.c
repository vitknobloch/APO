/* Implementation of the subroutine toplevel_fnc */

#include "subroutine.h"

#include <unistd.h>

char out[2] = {0x5c, 0x5f};

int toplevel_fnc(void)
{
  int r;
  while ((r = subroutine_fnc(0)) > 0)
  {
    if (r == 95)
    {
      int rw = write(1, &out, 2);
      if (rw <= 0)
      {
        return -1;
      }
    }
    else
    {
      int rw = write(1, &r, 1);
      if (rw < 0)
      {
        return -1;
      }
    }
  }
  return 0;
}
