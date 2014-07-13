
#include "singlylinked.h"

int
main() {
  int_list ints;
  int_link link1, link2;

  link1.value = 123;
  link2.value = 456;
   
  insert_head( &ints, &link1 );
  print_links( &ints );

  insert_after( &link1, &link2 );
  print_links( &ints );

  delete_after( &link1 );
  print_links( &ints );

  delete_head( &ints );
  print_links( &ints );
 
  return 0;
}
