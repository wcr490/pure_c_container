#include "../lib/include/arr.h"
#include <assert.h>
#include <stdlib.h>

struct Node {
  char head;
  char tail;
};

int main(void) {
  int flag;
  struct pure_arr *arr;

  if ((flag = pure_arr_new(&arr, 11, sizeof(struct Node)))) {
    printf("new failed: %d\n", flag);
  }

  struct Node n;
  n.head = 99;
  n.tail = 2;

  assert((flag = pure_arr_set(arr, 1, &n) == 0));
  struct pure_arr_iter iter;
  assert(pure_arr_iter_init(&iter, arr) == 0);
  struct Node *nn = malloc(sizeof(struct Node));
  nn->head = 0;
  nn->tail = 0;
  struct Node *tmp;
  assert(pure_arr_iter_next(&iter, (void **)&tmp, NULL) == 0);
  nn->head = tmp->head;
  nn->tail = tmp->tail;
  assert(pure_arr_iter_next(&iter, (void **)&tmp, NULL) == 0);
  nn->head = tmp->head;
  nn->tail = tmp->tail;
  assert(nn->head == 99);
  assert(nn->tail == 2);
  free(nn);
  assert(!pure_arr_del(arr));
  return 0;
}
