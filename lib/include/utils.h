#ifndef __UTILS_H
#define __UTILS_H

#include "stddef.h"

/* Iterator */
typedef int (*iter_next_fn_t)(void *self, void **item, size_t *index);
struct iter_i {
  iter_next_fn_t next;
};
static inline int iter_next(struct iter_i *self, void *item, size_t *index) {
  return (self->next(self, (void **)item, index));
}

/* Common Pointer to Function */
typedef int (*cmp_fn_t)(void *left, void *right);
typedef void (*del_fn_t)(void *del_item);

/* Common Check */
int double_ptr_check(void *ptr);
#endif // !__UTILS_H
