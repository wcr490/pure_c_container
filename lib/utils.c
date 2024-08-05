#include "utils.h"

int double_ptr_check(void *ptr) {
  if (ptr == NULL)
    return 1;
  *(void **)ptr = NULL;
  return 0;
}
