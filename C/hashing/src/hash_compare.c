#include <stdio.h>
#include <string.h>
#include "hashers.h"

int
main (void)
{
  unsigned long hash;
  unsigned long slen;
  char          *str;

  str = "Test string";
 
  slen = (unsigned long) strlen(str); 

  printf("The length of '%s' is %u.\n", str, slen); 

  printf("hash_sdbm is '%u'.\n", hash_sdbm(str, slen));
  printf("hash_djb2 is '%u'.\n", hash_djb2(str, slen));
   
  return 0;
}
