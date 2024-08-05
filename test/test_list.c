#include "../lib/include/list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Data {
  int d1, d2;
};

int main() {
  struct pure_list *list;
  assert(!pure_list_new(&list));
  assert(list != NULL);
  struct Data *d1 = malloc(sizeof(struct Data));
  struct Data *d2 = malloc(sizeof(struct Data));
  struct Data *d3 = malloc(sizeof(struct Data));
  struct Data *ret;

  d1->d1 = 1, d1->d2 = 2;
  assert(!pure_list_insert_tail(list, d1));

  d2->d1 = 3, d2->d2 = 4;
  assert(!pure_list_insert_tail(list, d2));

  d3->d1 = 5, d3->d2 = 6;
  assert(!pure_list_insert_tail(list, d3));

  pure_list_get_head_data(list, (void **)&ret);
  assert(ret->d1 == 1 && ret->d2 == 2);

  // pure_list_del_with_fn_t(list, free);
  pure_list_del_with_fn_t(list, free);
  // free(d1);
  // free(d2);
  // free(d3);
  free(list);
  return 0;
}
