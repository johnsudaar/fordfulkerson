#include "listes.h"

list* newList(int value){
  list *l = malloc(sizeof(list));
  l->value = value;
  l->next = NULL;
  return l;
}

int getList(list* l, int index){
  list* cur = l;
  int i = 0;
  for(i = 0; i < index; i++){
    if(cur->next != NULL) {
      cur = cur->next;
    } else {
      fprintf(stderr, "getList cannot get value %d (list size : %d)\n", index, i+1);
      return -1;
    }
  }

  return cur->value;
}
int setList(list* l, int index, int value){
  list* cur = l;
  int i = 0;

  for(i=0; i < index; i++) {
    if(cur->next != NULL){
      cur = cur->next;
    } else {
      return 0;
    }
  }
  cur->value = value;
  return 1;
}
int addToList(list* l, int value){
  list* cur = l;
  while(cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = newList(value);
  return cur->next != NULL;
}

int addToFront(list** l, int value){
  list* new = newList(value);
  new->next = (*l);
  (*l) = new;
  return new != NULL;
}

void printList(list* l){
  int first = 1;
  list* cur = l;
  while(cur != NULL){
    if(first){
      first = 0;
    } else {
      printf(", ");
    }
    printf("%d", cur->value);
    cur = cur->next;
  }

  printf("\n");
}

void freeList(list* l){
	if(l == NULL){
		return;
	}
	freeList(l->next);
  free(l);
}

int listSize(list* l){
  if(l == NULL){
    return 0;
  }else {
    return 1+listSize(l->next);
  }
}

int sequenceInList(list* l, int v1, int v2){
  if(listSize(l) < 2){
    return 0;
  }
  int i;
  int size = listSize(l);
  for(i = 0; i < size -1; i++){
    if(getList(l, i) == v1 && getList(l, i+1) == v2){
      return 1;
    }
  }
  return 0;
}

list* addOrInit(list* l, int value){
  if(l == NULL){
    return newList(value);
  }else {
    addToList(l,value);
    return l;
  }
}

list* copy(list* l){
  list* k = NULL;
  int i;
  for(i = 0; i < listSize(l); i++){
    k = addOrInit(k, getList(l, i));
  }
  return k;
}