//
// Created by Tianqi Liu on 2018-01-07.
//

#ifndef WD_LIBRARY_CONTAINER_H
#define WD_LIBRARY_CONTAINER_H

#include <stdlib.h>
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
