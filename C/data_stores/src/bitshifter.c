#include <stdio.h>

int main ()
{
  int small  = 8;
  int medium = 256;
  int large  = 65535;

  printf("bit shift small (%d) with 0: %d  1: %d  2: %d\n",
    small,
    small << 0,
    small << 1,
    small << 2
  );

  printf("bit shift medium (%d) with 0: %d  1: %d  2: %d\n",
    medium,
    medium << 0,
    medium << 1,
    medium << 2
  );

  printf("bit shift large (%d) with 0: %d  1: %d  2: %d\n",
    large,
    large << 0,
    large << 1,
    large << 2
  );

  return 0;
}
