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
  Xormodule	*new = malloc(sizeof(*new));
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

/*
 * Push Methods
 */

static int
Xor_emptypush(Xorlist *list, void *elem) {
  Xormodule	*new;

  if (!(new = Xor_newmodule(elem, NULL, NULL)))
    return (EXIT_FAILURE);
  list->first = new;
  list->last = new;
  list->size = 1;
  return (EXIT_SUCCESS);
}

static int
Xor_push_go(Xorlist *list, Xormodule **fl, void *elem) {
  Xormodule	*ref = *fl, *prev, *new;

  if (!ref)
    return (Xor_emptypush(list, elem));
  prev = XOR_KEY_ADDR(NULL, ref->key);
  if (!(new = Xor_newmodule(elem, ref, NULL)))
    return (EXIT_FAILURE);
  ref->key = XOR_KEY(prev, new);
  *fl = new;
  ++list->size;
  return (EXIT_SUCCESS);
}

int
Xor_pushback(Xorlist *list, void *elem) {
  return (Xor_push_go(list, &list->last, elem));
}

int
Xor_pushfront(Xorlist *list, void *elem) {
  return (Xor_push_go(list, &list->first, elem));
}

/*
 * Pop Methods
 */

static int
Xor_pop_go(Xormodule **flp, Xormodule **fln) {
  Xormodule	*p, *next, *pnext;

  if (!(p = *flp))
    return (EXIT_FAILURE);
  if (*flp == *fln) {
    *flp = NULL;
    *fln = NULL;
    free(p);
    return (EXIT_SUCCESS);
  }
  next = XOR_KEY_ADDR(NULL, p->key); // Should never equals NULL so no check
  pnext = XOR_KEY_ADDR(p, next->key);
  free(p);
  next->key = XOR_KEY(NULL, pnext);
  *flp = next;
  return (EXIT_SUCCESS);
}

int
Xor_popfront(Xorlist *list) {
  return (Xor_pop_go(&list->first, &list->last));
}

int
Xor_popback(Xorlist *list) {
  return (Xor_pop_go(&list->last, &list->first));
}
