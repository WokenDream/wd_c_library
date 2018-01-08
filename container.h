//
// Created by Tianqi Liu on 2018-01-07.
//

#ifndef WD_LIBRARY_CONTAINER_H
#define WD_LIBRARY_CONTAINER_H

#include <stdlib.h>

struct wd_stack;

struct wd_stack* create_stack(size_t ele_size);
int ensure_stack_capacity(struct wd_stack* stack, size_t num_of_element);
int stack_push(struct wd_stack* stack, void* val);
void* stack_pop(struct wd_stack* stack);
int stack_clear(struct wd_stack* stack);
void stack_destroy(struct wd_stack** stack);
size_t stack_len(struct wd_stack* stack);


struct linked_list_t;

struct linked_list_t* create_linked_list(size_t ele_size);
int linked_list_prepend(struct linked_list_t* list, void* val);
int linked_list_append(struct linked_list_t* list, void* val);
void* linked_list_remove_first(struct linked_list_t* list);
void* linked_list_remove_last(struct linked_list_t* list);
void* linked_list_remove_ith(struct linked_list_t* list, size_t index);
size_t linked_list_len(struct linked_list_t* list);


struct wd_queue;

struct wd_queue* wd_create_queue(size_t ele_size);
int wd_enqueue(struct wd_queue* queue, void* data);
int wd_dequeue(struct wd_queue* queue, void* data);
int wd_queue_size(struct wd_queue* queue);


struct wd_deque;

struct wd_deque* wd_create_deque(size_t ele_size);
int wd_deque_add_last(struct wd_deque* deque, void* data);
int wd_deque_remove_last(struct wd_deque* deque, void* data);
int wd_deque_add_first(struct wd_deque* deque, void* data);
int wd_deque_remove_first(struct wd_deque* deque, void* data);
int wd_deque_size(struct wd_deque* deque);


struct wd_heap;

struct wd_heap* wd_create_heap(size_t ele_size, int (*compare)(const void* a, const void* b));
int wd_heap_peak(struct wd_heap* heap, void* data);
int wd_heap_pop(struct wd_heap* heap, void* data);
int wd_heap_insert(struct wd_heap* heap, void* data);
size_t wd_heap_size(struct wd_heap* heap);
struct wd_heap* wd_array_to_heap(void* data, size_t len, size_t ele_size, int (*compare)(const void* a, const void* b));

#endif //WD_LIBRARY_CONTAINER_H
