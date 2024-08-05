#ifndef __LIST_H
#define __LIST_H

#include "utils.h"
#include <stddef.h>

/* In a `pure_list`
 *
               tail                          head
               back    next <--|--> prev    front
 *             |______________Node______________|
 *             ^                                ^
 *             |-----prev-----root-----next-----|
 */

struct pure_list_node {
  struct pure_list_node *prev;
  struct pure_list_node *next;
  union {
    void *data;
    size_t size;
  };
};
/* Memory Management */
/* Insert & Remove */
int pure_list_node_insert_front(struct pure_list_node *self, void *data);
int pure_list_node_insert_back(struct pure_list_node *self, void *data);
int pure_list_node_remove_front(struct pure_list_node *self, void **result);
int pure_list_node_remove_back(struct pure_list_node *self, void **result);

int pure_list_node_del_and_move_next(struct pure_list_node **self,
                                     del_fn_t del_fn);
int pure_list_node_del_and_move_prev(struct pure_list_node **self,
                                     del_fn_t del_fn);

struct pure_list {
  struct pure_list_node *root;
};

/* Memory Management */
int pure_list_new(struct pure_list **self);
int pure_list_init(struct pure_list *self, struct pure_list_node *root);
int __pure_list_del(struct pure_list *self);
int pure_list_del_with_fn_t(struct pure_list *self, del_fn_t del_fn);
/* Insert & Remove */
int pure_list_insert_head(struct pure_list *self, void *data);
int pure_list_insert_tail(struct pure_list *self, void *data);
int pure_list_remove_head(struct pure_list *self, void **result);
int pure_list_remove_tail(struct pure_list *self, void **result);

/* Query */
int pure_list_is_empty(struct pure_list *self); /* return the result */
int pure_list_len(struct pure_list *self);
int pure_list_get_head(struct pure_list *self, struct pure_list_node **result);
int pure_list_get_tail(struct pure_list *self, struct pure_list_node **result);
int pure_list_get_head_data(struct pure_list *self, void **result);
int pure_list_get_tail_data(struct pure_list *self, void **result);

/* Iterator */
struct pure_list_iter {
  struct iter_i *iterator;
  struct pure_list *list;
  struct pure_list_node *cur;
  size_t index;
  int direction;
};
int pure_list_iter_new(struct pure_list_iter **iter, struct pure_list *list,
                       int direction);
int pure_list_iter_init(struct pure_list_iter *iter, struct pure_list *list,
                        int direction);
int pure_list_iter_next(struct pure_list_iter *iter, void **item,
                        size_t *index);
int pure_list_iter_step(struct pure_list_iter *iter);

#endif // !__LIST_H
