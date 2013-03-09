#include <stdio.h>
#include <string.h>
#include "hashers.h"

int
hashup(char *str, unsigned long slen)
{
  printf("%s,%u,%u,%u\n", str, slen, hash_sdbm(str, slen), hash_djb2(str, slen));
  return 0;
}

int
main (int argc, char **argv)
{
  unsigned long hash;
  char          *in_s, *cr;
  size_t        *len;

  printf("String,length,hash_sdbm,hash_djb2\n");
  
  while ( in_s = fgetln(stdin, &len) ) {
    cr = strchr(in_s, '\n');
    *cr = '\0';
    hashup(in_s, (unsigned long) len);
  }

  return 0;
}
