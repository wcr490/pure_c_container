#ifndef __ARR_H
#define __ARR_H

#include "malloc.h"
#include "stddef.h"
#include "string.h"

#include "utils.h"

struct pure_arr {
  unsigned char *data;
  size_t ele_nums;
  size_t ele_size;
};

struct pure_arr_iter {
  struct iter_i *iterator;
  struct pure_arr *data;
  size_t cursor;
};

#ifndef NO_MALLOC

int pure_arr_new(struct pure_arr **self, size_t ele_nums, size_t ele_size);
int pure_arr_del(struct pure_arr *self);

#endif

int pure_arr_init(struct pure_arr *self, unsigned char *data, size_t ele_nums,
                  size_t ele_size);
/* Unsafe function (Don't use them directly) */
static inline int __pure_arr_get(struct pure_arr *self, size_t index,
                                 void *result) {
  memcpy(result, self->data + index * self->ele_size, self->ele_size);
  return 0;
}
static inline int __pure_arr_get_ref(struct pure_arr *self, size_t index,
                                     void **result_ref) {
  *result_ref = self->data + self->ele_size * index;
  return 0;
}
static inline int __pure_arr_set(struct pure_arr *self, size_t index,
                                 void *data) {
  memcpy(self->data + index * self->ele_size, data, self->ele_size);
  return 0;
}
int pure_arr_get(struct pure_arr *self, size_t index, void *result);
int pure_arr_get_ref(struct pure_arr *self, size_t index, void **result_ref);
int pure_arr_set(struct pure_arr *self, size_t index, void *data);

int pure_arr_is_valid_index(struct pure_arr *self, size_t index);
void pure_arr_swap(struct pure_arr *self, size_t i, size_t j);

int pure_arr_iter_init(struct pure_arr_iter *self, struct pure_arr *data);
int pure_arr_iter_next(struct pure_arr_iter *self, void **item, size_t *index);

#endif
