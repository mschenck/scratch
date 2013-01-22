#include <unistd.h>
#include <stdio.h>

int
main (void)
{
  int pageSize = getpagesize();
  
  printf("Page size on your system = %i bytes\n", pageSize);
  
  return 0;
}
