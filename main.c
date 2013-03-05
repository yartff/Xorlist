#include	<stdlib.h>
#include	<stdio.h>
#include	<stdint.h>
#include	"xorlist.h"

static int	tab[] = {5, 3, 1, 2, 7, 4, 0, 6};

int
sort(void *a, void *b) {
  return (*(int *)a < *(int *)b);
}
void
dump_it(void *t) {
  printf("%d\n", *(int *)t);
}

int
list_filler(Xorlist list) {
  // Initializing the list by pushing back several values
  unsigned int	i = 0;
  while (i < sizeof(tab) / sizeof(*tab)) {
    if (Xor_pushback(list, tab + i) == EXIT_FAILURE)
      return (EXIT_FAILURE);
    ++i;
  }
  return (EXIT_SUCCESS);
}

int
main() {
  Xorlist	list = Xor_create();

#if 0
  printf("size of list: %ld\n", sizeof(Xorlist));
  if (!list)
    return (EXIT_FAILURE);
  Xor_foreach(list, &dump_it);
  if (list_filler(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  printf("=====================\nPoping front:\n");
  do {
    printf("--\n");
    Xor_foreach(list, &dump_it);
  } while (Xor_popfront(list) == EXIT_SUCCESS);
  if (list_filler(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  printf("=====================\nPoping back:\n");
  do {
    printf("--\n");
    Xor_foreach(list, &dump_it);
  } while (Xor_popback(list) == EXIT_SUCCESS);
#endif
  if (list_filler(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);

  int	retab[] = {-1, 12, 5};
  unsigned int	i = 0;
  while (i < sizeof(retab) / sizeof(*retab)) {
    if (Xor_push_into(list, &retab[i], sort) == EXIT_FAILURE)
      return (EXIT_FAILURE);
    ++i;
  }
  printf("=====================\nSorting:\n");
  Xor_sort(list, sort);
  printf("Foreach:\n");
  Xor_foreach(list, &dump_it);
  printf("Foreach_rev:\n");
  Xor_foreach_rev(list, &dump_it);
  return (Xor_destroy(list));
}
