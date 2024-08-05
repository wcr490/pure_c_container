#include "./include/stack.h"
#include "./include/arr.h"
#include <stdlib.h>

struct stack_i pure_stack_i = {
    .push = (stack_push_fn_t)pure_stack_push,
    .pop = (stack_pop_fn_t)pure_stack_pop,
    .peek = (stack_peek_fn_t)pure_stack_peek,
};

/* Basic Interfaces */
int pure_stack_push(struct pure_stack *self, void *data) {
  if (pure_arr_set(self->data, self->top, data))
    return 1;
  self->top++;
  return 0;
}
int pure_stack_pop(struct pure_stack *self, void *result) {
  if (self->top == 0)
    return 1;
  self->top--;
  __pure_arr_get(self->data, self->top, result);
  return 0;
}
int pure_stack_peek(struct pure_stack *self, void *result) {
  if (self->top == 0)
    return 1;
  __pure_arr_get(self->data, self->top - 1, result);
  return 0;
}
/* Memory management */
int pure_stack_new(struct pure_stack **self, size_t ele_nums, size_t ele_size) {
  struct pure_stack *tmp;
  struct pure_arr *data;
  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return 1;
  if (pure_arr_new(&data, ele_nums, ele_size)) {
    free(tmp);
    return 2;
  }
  if (pure_stack_init(tmp, data)) {
    free(tmp);
    free(data);
    return 3;
  }
  *self = tmp;
  return 0;
}
int pure_stack_init(struct pure_stack *self, struct pure_arr *data) {
  self->top = 0, self->data = data, self->interface = &pure_stack_i;
  return 0;
}
int pure_stack_del(struct pure_stack *self) {
  if (pure_arr_del(self->data)) {
    return 1;
  }
  free(self);
  return 0;
}

/* Query */
int pure_stack_len(struct pure_stack *self) { return self->top; }
int pure_stack_remaining_space(struct pure_stack *self) {
  return self->data->ele_nums - self->top;
}
