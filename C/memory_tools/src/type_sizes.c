
#include <stdio.h>

void
pp(char* type, int size)
{
    printf("The size of a '%s':\t\t\t\t %d\n", type, size);
}

int
main(void)
{
  int                       i;
  unsigned int              ui;
  long                      l;
  unsigned long             ul;
  float                     f;
  char                      c;

  pp("char", sizeof(c));
  pp("int", sizeof(i));
  pp("unsigned int", sizeof(ui));
  pp("float", sizeof(f));
  pp("long", sizeof(l));
  pp("unsigned long", sizeof(ul));

  return 0;
}
