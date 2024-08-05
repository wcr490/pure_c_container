#include "../lib/include/stack.h"
#include "assert.h"

struct Node {
  char head;
  char tail;
};

int main() {
  struct pure_stack *stack;
  pure_stack_new(&stack, 10, sizeof(struct Node));
  pure_stack_push(stack, (void *)&(struct Node){1, 2});
  pure_stack_push(stack, (void *)&(struct Node){3, 4});
  struct Node ret;
  assert(pure_stack_len(stack) == 2);
  pure_stack_pop(stack, &ret);
  assert(pure_stack_len(stack) == 1);
  assert(ret.head == 3 && ret.tail == 4);
  pure_stack_peek(stack, &ret);
  assert(ret.head == 1 && ret.tail == 2);
  pure_stack_del(stack);
}
