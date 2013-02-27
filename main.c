#include	<stdlib.h>
#include	<stdio.h>
#include	<stdint.h>
#include	"xorlist.h"

int	tab[] = {600, 52, 50, 10, 284, 6465};
void
dump_it(void *t) {
  printf("%d\n", *(int *)t);
}

int
list_filler(Xorlist list) {
  // Initializing the list by pushing back several values
  unsigned int	i = 0;
  while (i < sizeof(tab) / sizeof(*tab)) {
    if (Xor_pushfront(list, tab + i) == EXIT_FAILURE)
      return (EXIT_FAILURE);
    ++i;
  }
  return (EXIT_SUCCESS);
}

int
main() {
  Xorlist	list = Xor_create();

  printf("size of list: %ld\n", sizeof(Xorlist));
  if (!list)
    return (EXIT_FAILURE);
  Xor_foreach(list, &dump_it);
  if (list_filler(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  printf("Poping front:\n");
  do {
    printf("Foreach:\n");
    Xor_foreach(list, &dump_it);
  } while (Xor_popfront(list) == EXIT_SUCCESS);
  if (list_filler(list) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  printf("Poping back:\n");
  do {
    printf("Foreach:\n");
    Xor_foreach(list, &dump_it);
  } while (Xor_popback(list) == EXIT_SUCCESS);
  return (Xor_destroy(list));
}
