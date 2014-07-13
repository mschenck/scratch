#ifndef SINGLYLINKED_H
#define SINGLYLINKED_H

typedef struct {
  int      value;
  void    *next;
} int_link;

typedef struct {
  int_link *head;
} int_list;



void insert_head( int_list*, int_link* );

void delete_head( int_list* );

void insert_after( int_link*, int_link* );

void delete_after( int_link* );

#endif
