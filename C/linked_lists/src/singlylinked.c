#include "singlylinked.h"

#include <stdlib.h>
#include <stdio.h>

void
insert_head( int_list* list, int_link* new_link )
{
  printf("insert_head( int_list* list, int_link* new_link )\n");

  new_link->next = list->head;
  list->head = new_link;
}

void
delete_head( int_list* list )
{
  printf("delete_head( int_list* list )\n");
  int_link *buffer = list->head;
  list->head = buffer->next;

  printf("free( %p )\n", buffer);
//  free( buffer );
}

void
insert_after( int_link* after_this, int_link* new_link )
{
  printf("insert_after( int_link* after_this, int_link* new_link )\n");
  
  int_link *buffer = after_this->next;
  after_this->next = new_link;
  new_link->next = buffer;
}

void
delete_after( int_link* link )
{
  printf("delete_after( int_link* link )\n");

  int_link *buffer = link->next;
  link->next = buffer->next;

  printf("free( %p )\n", buffer);
//  free( buffer );
}

void
print_links( int_list* list )
{
  int_link  *ptr;

  printf("+ print_links( int_list* list )\n");

  for ( ptr = list->head; ptr != NULL; ptr = ptr->next ) {
    printf( "  - link(%p) = %d\n", ptr, ptr->value );
  }

  printf("\n");
}
