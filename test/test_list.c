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

  d1->d1 = 1;
  d1->d2 = 2;
  assert(!pure_list_insert_tail(list, d1));

  d2->d1 = 3;
  d2->d2 = 4;
  assert(!pure_list_insert_tail(list, d2));

  d3->d1 = 5;
  d3->d2 = 6;
  assert(!pure_list_insert_tail(list, d3));

  pure_list_get_head_data(list, (void **)&ret);
  assert(ret->d1 == 1 && ret->d2 == 2);

  pure_list_del_with_fn_t(list, free);
  free(list);

  struct pure_list *l;
  assert(!pure_list_new(&l));
  assert(l != NULL);

  struct Data *d4 = malloc(sizeof(struct Data));
  struct Data *d5 = malloc(sizeof(struct Data));
  struct Data *d6 = malloc(sizeof(struct Data));
  void *ret_;

  d4->d1 = 1;
  d4->d2 = 2;
  assert(!pure_list_insert_tail(l, d4));

  d5->d1 = 3;
  d5->d2 = 4;
  assert(!pure_list_insert_tail(l, d5));

  d6->d1 = 5;
  d6->d2 = 6;
  assert(!pure_list_insert_tail(l, d6));

  struct pure_list_iter *i;
  size_t index;
  assert(!pure_list_iter_new(&i, l, 0));
  pure_list_iter_next(i, &ret_, &index);
  struct Data *data = (struct Data *)ret_;
  assert(data->d1 == 1 && data->d2 == 2 && index == 0);
  /* while (pure_list_iter_next(i, &ret_, NULL) == 0) {
    struct Data *data = (struct Data *)ret_;
    printf("d1: %d, d2: %d\n", data->d1, data->d2);
  } */

  pure_list_del_with_fn_t(l, free);
  free(i);
  free(l);

  return 0;
}
