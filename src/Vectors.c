#include <stdlib.h>

#include "../include/Vectors.h"

Vector_t Vector_new() {
  Vector_t vec = malloc(sizeof(Vector));
  vec->size = 0;
  vec->head = NULL;
  return vec;
}
int Vector_isempty(Vector_t vec) { return vec->size == 0; }

void Vector_push(Vector_t vec, Any_t elem) {
  if (Vector_isempty(vec)) {
    vec->head = Node_new(elem);
  } else [[clang::likely]] {
    Node_t tmp = vec->head;
    /*
     * O(n)
     *
     */
    while (tmp->next) {
      tmp = tmp->next;
    }
    tmp->next = Node_new(elem);
  }
  vec->size++;
}

typedef Any_t (*MapFn)(Any_t vec_item);

typedef void (*ReduceFn)(Any_t vec_item, Any_t acc);

typedef int (*FilterFn)(Any_t vec_item);

Vector_t Vector_map(Vector_t vec, MapFn fn) {
  Vector_t new_vec = Vector_new();
  Node_t tmp = vec->head;
  while (tmp) {
    Vector_push(new_vec, fn(tmp->data));
    tmp = tmp->next;
  }
  return new_vec;
}

void Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc) {
  Node_t tmp = vec->head;
  while (tmp) {
    fn(tmp->data, acc);
    tmp = tmp->next;
  }
}

Vector_t Vector_filter(Vector_t vec, FilterFn fn) {
  Vector_t filter_vec = Vector_new();

  Node_t tmp = vec->head;
  while (tmp) {
    if (fn(tmp->data)) {
      Vector_push(filter_vec, tmp->data);
    }
    tmp = tmp->next;
  }

  return filter_vec;
}