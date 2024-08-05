#include "./include/list.h"
#include <stdio.h>
#include <stdlib.h>

int pure_list_node_insert_front(struct pure_list_node *self, void *data) {
  struct pure_list_node *inserted_node = malloc(sizeof(struct pure_list_node));
  if (inserted_node == NULL)
    return 1;
  inserted_node->next = self->next;
  inserted_node->prev = self;
  inserted_node->next->prev = inserted_node;
  self->next = inserted_node;
  inserted_node->data = data;
  return 0;
}

int pure_list_node_insert_back(struct pure_list_node *self, void *data) {
  struct pure_list_node *inserted_node = malloc(sizeof(struct pure_list_node));
  if (inserted_node == NULL)
    return 1;
  inserted_node->next = self;
  inserted_node->prev = self->prev;
  inserted_node->prev->next = inserted_node;
  inserted_node->data = data;
  self->prev = inserted_node;
  inserted_node->data = data;
  return 0;
}

int pure_list_node_remove_front(struct pure_list_node *self, void **result) {
  if (self == NULL)
    return 1;
  struct pure_list_node *tmp = self->next;
  *result = tmp->data;
  self->next = tmp->next;
  self->next->prev = self;
  free(tmp);
  return 0;
}

int pure_list_node_remove_back(struct pure_list_node *self, void **result) {
  if (self == NULL)
    return 1;
  struct pure_list_node *tmp = self->prev;
  *result = tmp->data;
  self->prev = tmp->prev;
  self->prev->next = self;
  free(tmp);
  return 0;
}

/* These two Functions
 * Focus on `pure_list_node`, so don't mind what `pure_list` should do */
int pure_list_node_del_and_move_next(struct pure_list_node **self,
                                     del_fn_t del_fn) {
  struct pure_list_node *next, *cur;
  cur = *self;
  next = cur->next;
  if (del_fn == NULL) {
    free(cur);
    *self = next;
    return 0;
  }
  /* FIX_IT: Error handling
   */
  del_fn(cur->data);
  free(cur);
  *self = next;
  return 0;
}
int pure_list_node_del_and_move_prev(struct pure_list_node **self,
                                     del_fn_t del_fn) {
  struct pure_list_node *prev, *cur;
  cur = *self;
  prev = cur->prev;
  if (del_fn == NULL) {
    free(cur);
    *self = prev;
    return 0;
  }
  /* FIX_IT: Error handling
   */
  del_fn(cur->data);
  free(cur);
  *self = prev;
  return 0;
}

int pure_list_new(struct pure_list **self) {
  struct pure_list *nl = malloc(sizeof(struct pure_list));
  if (nl == NULL)
    return 1;
  struct pure_list_node *r = malloc(sizeof(struct pure_list_node));
  pure_list_init(nl, r);
  *self = nl;
  return 0;
}
int pure_list_init(struct pure_list *self, struct pure_list_node *root) {
  self->root = root;
  self->root->prev = root, self->root->next = root, self->root->size = 0;
  return 0;
}
/* Definitely Causing Unsafe Memory leaks */
/* Don't use it in a casual way */
int __pure_list_del(struct pure_list *self) {
  if (self == NULL)
    return 1;
  struct pure_list_node *node = self->root->next;
  while (node != self->root) {
    if (pure_list_node_del_and_move_next(&node, NULL))
      return 2;
  }
  free(self->root);
  return 0;
};
int pure_list_del_with_fn_t(struct pure_list *self, del_fn_t del_fn) {
  if (del_fn == NULL)
    return __pure_list_del(self);
  if (self == NULL)
    return 1;
  struct pure_list_node *node = self->root->next;
  while (node != self->root) {
    if (pure_list_node_del_and_move_next(&node, del_fn))
      return 2;
  }
  free(self->root);
  return 0;
}

int pure_list_insert_head(struct pure_list *self, void *data) {
  if (pure_list_node_insert_front(self->root, data))
    return 1;
  self->root->size++;
  return 0;
}
int pure_list_insert_tail(struct pure_list *self, void *data) {
  if (pure_list_node_insert_back(self->root, data))
    return 1;
  self->root->size++;
  return 0;
}
int pure_list_remove_head(struct pure_list *self, void **result) {
  if (pure_list_node_remove_front(self->root, result))
    return 1;
  self->root->size--;
  return 0;
}
int pure_list_remove_tail(struct pure_list *self, void **result) {
  if (pure_list_node_remove_back(self->root, result))
    return 1;
  self->root->size--;
  return 0;
}

/* return the result */
int pure_list_is_empty(struct pure_list *self) {
  return self->root->prev == self->root;
}
int pure_list_len(struct pure_list *self) { return self->root->size; }
int pure_list_get_head(struct pure_list *self, struct pure_list_node **result) {
  if (self == NULL)
    return 1;
  if (pure_list_is_empty(self))
    return 2;
  *result = self->root->next->data;
  return 0;
}
int pure_list_get_tail(struct pure_list *self, struct pure_list_node **result) {
  if (self == NULL)
    return 1;
  if (pure_list_is_empty(self))
    return 2;
  *result = self->root->prev;
  return 0;
}
int pure_list_get_head_data(struct pure_list *self, void **result) {
  if (self == NULL)
    return 1;
  if (pure_list_is_empty(self))
    return 2;
  *result = self->root->next->data;
  return 0;
}
int pure_list_get_tail_data(struct pure_list *self, void **result) {
  if (self == NULL)
    return 1;
  if (pure_list_is_empty(self))
    return 2;
  *result = self->root->prev->data;
  return 0;
}

struct iter_i pure_list_iter_interface = {
    .next = (iter_next_fn_t)pure_list_iter_next,
};
int pure_list_iter_next(struct pure_list_iter *self, void **item,
                        size_t *index) {
  if (item == NULL)
    return 1;
  if (self->cur == self->list->root)
    return 2;
  *item = self->cur->data;
  if (index != NULL)
    *index = self->index;
  self->index++;
  pure_list_iter_step(self);
  return 0;
}
int pure_list_iter_new(struct pure_list_iter **iter, struct pure_list *list,
                       int direction) {
  struct pure_list_iter *tmp = malloc(sizeof(struct pure_list_iter));
  if (tmp == NULL)
    return 1;
  if (pure_list_iter_init(tmp, list, direction))
    return 2;
  pure_list_iter_step(tmp);
  *iter = tmp;
  return 0;
}
int pure_list_iter_init(struct pure_list_iter *iter, struct pure_list *list,
                        int direction) {
  iter->cur = list->root, iter->list = list, iter->direction = direction,
  iter->index = 0, iter->iterator = &pure_list_iter_interface;
  return 0;
}
int pure_list_iter_step(struct pure_list_iter *iter) {
  /* direction == 1 => move from the back to the front
   *              0 => move fron the front to the back
   */
  iter->cur = iter->direction ? iter->cur->prev : iter->cur->next;
  return 0;
}
