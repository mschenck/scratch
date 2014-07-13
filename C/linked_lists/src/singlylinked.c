#include "singlylinked.h"

#include <stdlib.h>
#include <stdio.h>

int_link* new_link()
{
  int_link *new_link = malloc( sizeof( int_link ) );

  (*new_link).next = NULL;

  return new_link; 
}

void
insert_head( int_list* list, int_link* new_link )
{

  new_link->next = list->head;
  list->head = new_link;
}

void
delete_head( int_list* list )
{
  int_link *buffer = list->head;
  list->head = buffer->next;

  free( buffer );
}

void
insert_after( int_link* after_this, int_link* new_link )
{
  
  int_link *buffer = after_this->next;
  after_this->next = new_link;
  new_link->next = buffer;
}

void
delete_after( int_link* link )
{

  int_link *buffer = link->next;
  link->next = buffer->next;

  free( buffer );
}

void
print_links( int_list* list )
{
  int_link  *ptr;

  fprintf( stdout,"+ print_links( int_list* list )\n");

  for ( ptr = list->head; ptr != NULL; ptr = ptr->next ) {
    fprintf( stdout, "  - link(%p) = %d\n", ptr, ptr->value );
  }

  fprintf( stdout,"\n");
}
