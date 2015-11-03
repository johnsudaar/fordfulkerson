#ifndef LISTES_CHAINEE_H
#define LISTES_CHAINEE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct list list;
struct list{
  int value;
  list* next;
};

list* newList(int value);
list* copy(list* l);
int listSize(list* l);
int getList(list* l, int index);
int setList(list* l, int index, int value);
int addToList(list* l, int value);
list* addOrInit(list* l, int value);
int addToFront(list** l, int value);
int sequenceInList(list* l, int v1, int v2);
void printList(list* l);
void freeList(list* l);


#endif