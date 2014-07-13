
#include <limits.h>
#include <stdio.h>
#include "singlylinked.h"

#define MAX_LINKS 65535

int
main() {
  int_list ints;
  int_link *link1, *link2;

  link1 = new_link();
  link2 = new_link();
  int x;

  (*link1).value = 123;
  (*link2).value = 456;
   
  insert_head( &ints, link1 );
  print_links( &ints );

  insert_after( link1, link2 );
  print_links( &ints );

  delete_after( link1 );
  print_links( &ints );

  delete_head( &ints );
  print_links( &ints );


  printf("Adding %d 1's to list\n", MAX_LINKS);
  for ( x = 0; x < MAX_LINKS; x++ ) {
    link1 = new_link();
    (*link1).value = 1;
    insert_head( &ints, link1 );
  }
  
  printf("Removing %d 1's from list\n", MAX_LINKS);
  for ( x = 0; x < MAX_LINKS; x++ ) {
    delete_head( &ints );
  }
 
  print_links( &ints );

  return 0;
}
