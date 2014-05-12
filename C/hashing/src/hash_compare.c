#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "hashers.h"

const char * TOPMILLION = "data/top-million.txt";

int
hashup(char *str, unsigned long slen)
{
  unsigned long hash;

  printf( "sdbm,\t %s,\t %u,\t '%u' \n", str, slen, hash_sdbm(str, slen) );
  printf( "djb2,\t %s,\t %u,\t '%u' \n", str, slen, hash_djb2(str, slen) );

  return 0;
}

int
main (int argc, char **argv)
{
  char          *in_s = NULL, *cr;
  size_t        len = 0;
  ssize_t       read;
  FILE          *topmill;

  topmill = fopen( TOPMILLION, "r" );
  if ( topmill == NULL ) {
    printf( "Failed to open '%s'\n", TOPMILLION );
    return -1;
  }

  printf("Function,\t string,\t length,\t hash\n");
  
  while ( (read = getline(&in_s, &len, topmill)) != -1 ) {
    cr = strchr( in_s, '\n' );
    *cr = '\0';
    hashup(in_s, (unsigned long) read);
    in_s = NULL;
    len  = 0;
  }

  free( topmill );
  return 0;
}
