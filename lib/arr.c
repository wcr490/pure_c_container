#include "./include/arr.h"

struct iter_i pure_arr_iter_interface = {
    .next = (iter_next_fn_t)pure_arr_iter_next,
};

/* Safe boundary checking */
int pure_arr_get(struct pure_arr *self, size_t index, void *result) {
  if (result == NULL)
    return 1;
  if (index >= self->ele_nums)
    return 2;
  __pure_arr_get(self, index, result);
  return 0;
}
int pure_arr_get_ref(struct pure_arr *self, size_t index, void **result_ref) {
  if (result_ref == NULL)
    return 1;
  if (index >= self->ele_nums) {
    return 2;
  }
  __pure_arr_get_ref(self, index, result_ref);
  return 0;
}
int pure_arr_set(struct pure_arr *self, size_t index, void *data) {
  if (data == NULL)
    return 1;
  if (index >= self->ele_nums)
    return 2;
  __pure_arr_set(self, index, data);
  return 0;
}
int pure_arr_init(struct pure_arr *self, unsigned char *data, size_t ele_nums,
                  size_t ele_size) {
  self->data = data, self->ele_nums = ele_nums, self->ele_size = ele_size;
  return 0;
}
void pure_arr_swap(struct pure_arr *self, size_t i, size_t j) {
  unsigned char tmp[self->ele_size];
  pure_arr_get(self, i, tmp);
  memcpy(self->data + i * self->ele_size, self->data + j * self->ele_size,
         self->ele_size);
  pure_arr_set(self, j, tmp);
}

#ifndef NO_MALLOC
int pure_arr_new(struct pure_arr **self, size_t ele_nums, size_t ele_size) {
  struct pure_arr *arr;
  unsigned char *data;
  arr = malloc(sizeof(*arr));
  if (arr == NULL)
    return 1;
  data = malloc(sizeof(ele_nums * ele_size));
  if (data == NULL) {
    free(arr);
    return 2;
  }
  if (pure_arr_init(arr, data, ele_nums, ele_size)) {
    free(arr);
    free(data);
    return 3;
  }
  *self = arr;
  return 0;
}

int pure_arr_del(struct pure_arr *self) {
  free(self->data);
  free(self);
  return 0;
}

int pure_arr_iter_init(struct pure_arr_iter *self, struct pure_arr *data) {
  if (data == NULL)
    return 1;
  self->cursor = 0;
  self->data = data;
  self->iterator = &pure_arr_iter_interface;
  return 0;
}
int pure_arr_iter_next(struct pure_arr_iter *self, void **item, size_t *index) {
  int flag;
  if (double_ptr_check(item))
    return 1;
  if (pure_arr_get_ref(self->data, self->cursor, item))
    return 2;
  if (index != NULL)
    *index = self->cursor;
  self->cursor++;
  return 0;
}

#endif
