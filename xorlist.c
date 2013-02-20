#include	<stdio.h>
//
#include	<stdlib.h>
#include	<string.h>
#include	<stdlib.h>
#include	"xorlist.h"

Xorlist *
Xor_create(void) {
  Xorlist	*list;
  if (!(list = malloc(sizeof(*list))))
    return (NULL);
  memset(list, 0, sizeof(*list));
  return (list);
}

static	Xormodule *
Xor_newmodule(void *elem, void *kp, void *kn) {
  Xormodule	*new = malloc(sizeof(Xormodule *));
  if (!new)
    return (NULL);
  new->elem = elem;
  new->key = XOR_KEY(kp, kn);
  return (new);
}

static void
Xor_foreach_go(Xormodule *begin, void (*callback)(void *)) {
  Xormodule	*prev = NULL, *swap_tmp;
  while (begin) {
    callback(begin->elem);
    swap_tmp = XOR_KEY_ADDR(prev, begin->key);
    prev = begin;
    begin = swap_tmp;
  }
}

void
Xor_foreach_rev(Xorlist *list, void (*callback)(void *)) {
  Xor_foreach_go(list->last, callback);
}

void
Xor_foreach(Xorlist *list, void (*callback)(void *)) {
  Xor_foreach_go(list->first, callback);
}

int
Xor_emptypush(Xorlist *list, void *elem) {
  Xormodule	*new;

  if (!(new = Xor_newmodule(elem, NULL, NULL)))
    return (EXIT_FAILURE);
  list->first = new;
  list->last = new;
  list->size = 1;
  return (EXIT_SUCCESS);
}

int
Xor_pushback(Xorlist *list, void *elem) {
  Xormodule	*ref = list->last, *prev, *new;

  if (!ref)
    return (Xor_emptypush(list, elem));
  prev = XOR_KEY_ADDR(NULL, ref->key);
  if (!(new = Xor_newmodule(elem, ref, NULL)))
    return (EXIT_FAILURE);
  ref->key = XOR_KEY(prev, new);
  list->last = new;
  ++list->size;
  return (EXIT_SUCCESS);
}
