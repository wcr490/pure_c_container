#ifndef __STACK_H
#define __STACK_H

#include "arr.h"
#include <stddef.h>

struct pure_stack {
  struct pure_arr *data;
  struct stack_i *interface;
  size_t top;
};

typedef int (*stack_push_fn_t)(struct pure_stack *self, void *data);
typedef int (*stack_pop_fn_t)(struct pure_stack *self, void **result);
typedef int (*stack_peek_fn_t)(struct pure_stack *self, void **result);

struct stack_i {
  stack_push_fn_t push;
  stack_pop_fn_t pop;
  stack_peek_fn_t peek;
};

/* Basic Interfaces */
static inline int pure_stack_push_i(struct pure_stack *self, void *data) {
  return (self->interface->push(self, data));
}
static inline int pure_stack_pop_i(struct pure_stack *self, void **result) {
  return (self->interface->pop(self, result));
}
static inline int pure_stack_peek_i(struct pure_stack *self, void **result) {
  return (self->interface->peek(self, result));
}
int pure_stack_push(struct pure_stack *self, void *data);
int pure_stack_pop(struct pure_stack *self, void *data);
int pure_stack_peek(struct pure_stack *self, void *data);

/* Memory management */
int pure_stack_new(struct pure_stack **self, size_t ele_nums, size_t ele_size);
int pure_stack_init(struct pure_stack *self, struct pure_arr *data);
int pure_stack_del(struct pure_stack *self);

/* Query */
int pure_stack_len(struct pure_stack *self);
int pure_stack_remaining_space(struct pure_stack *self);

#endif
