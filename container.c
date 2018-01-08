//
// Created by Tianqi Liu on 2018-01-07.
//

#include "container.h"
#include "string.h"

struct wd_stack {
    size_t cap;
    size_t len;
    size_t ele_size;
    char* array; // may be char*, will see
};

struct wd_stack* create_stack(size_t ele_size) {

    struct wd_stack* stack = (struct wd_stack* )malloc(sizeof(*stack));
    if (stack == NULL) {
        return NULL;
    }
    size_t cap = 8;
    stack->cap = cap;
    stack->len = 0;
    stack->ele_size = ele_size;
    stack->array = (char* )malloc(ele_size * cap);
    if (stack->array == NULL) {
        return NULL;
    }
    return stack;
}

int ensure_stack_capacity(struct wd_stack* stack, size_t new_cap) {
    if (stack == NULL) {
        return -1;
    }
    if (stack->cap >= new_cap) {
        return stack->cap;
    }
    stack->array = (char* )realloc(stack->array, stack->ele_size * new_cap);
    if (stack->array == NULL) {
        return -2;
    }
    stack->cap = new_cap;
    return 0;
}

int stack_push(struct wd_stack* stack, void* val) {
    if (stack == NULL || val == NULL) {
        return -1;
    }
    if (stack->len == stack->cap) {
        size_t new_cap = stack->cap << 1;
        stack->array = (char* )realloc(stack->array, stack->ele_size * new_cap);
        if (stack->array == NULL) {
            return -2;
        }
        stack->cap = new_cap;
    }
    memcpy(stack->array + stack->ele_size * stack->len, val, stack->ele_size);
    ++(stack->len);
    return 0;
}

void* stack_pop(struct wd_stack* stack) {
    if (stack == NULL) {
        return NULL;
    }
    void* popped_val = malloc(stack->ele_size);
    if (popped_val == NULL) {
        return NULL;
    }
    memcpy(popped_val, stack->array + stack->ele_size * (stack->len - 1), stack->ele_size);
    --(stack->len);
    size_t half_cap = stack->cap >> 1;
    if (stack->len < half_cap) {
        stack->array = (char* )realloc(stack->array, stack->ele_size * half_cap);
        stack->cap = half_cap;
    }
    return popped_val;
}

int stack_clear(struct wd_stack* stack) {
    if (stack == NULL) {
        return -1;
    }
    size_t cap = 4;
    stack->len = 0;
    stack->cap = cap;
    stack->array = realloc(stack->array, stack->ele_size * cap);
    return 0;
}

void stack_destroy(struct wd_stack** stack) {
    if (stack == NULL || * stack == NULL) {
        return;
    }
    free((*stack)->array);
    free(stack);
    *stack = NULL;
}

size_t stack_len(struct wd_stack* stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->len;
}

struct list_node {
    void* val;
    struct list_node* next;
};

struct linked_list_t {
    struct list_node* head;
    struct list_node* tail;
    size_t ele_size;
    size_t len;
};

struct linked_list_t* create_linked_list(size_t ele_size) {
    struct linked_list_t* list = (struct linked_list_t* )malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->ele_size = ele_size;
    list->len = 0;
    return list;
}

int linked_list_prepend(struct linked_list_t* list, void* val) {
    if (list == NULL || val == NULL) {
        return -1;
    }
    struct list_node* temp = (struct list_node* )malloc(sizeof(*temp));
    if (temp == NULL) {
        return -2;
    }
    temp->val = malloc(sizeof(list->ele_size));
    if (temp->val == NULL) {
        return -2;
    }
    memcpy(temp->val, val, list->ele_size);
    temp->next = list->head;

    list->head = temp;
    if (list->tail == NULL) {
        list->tail = temp;
    }
    ++(list->len);
    return 0;
}

int linked_list_append(struct linked_list_t* list, void* val) {
    if (list == NULL || val == NULL) {
        return -1;
    }
    struct list_node* temp = (struct list_node* )malloc(sizeof(*temp));
    if (temp == NULL) {
        return -2;
    }
    temp->val = malloc(sizeof(list->ele_size));
    if (temp->val == NULL) {
        return -2;
    }
    memcpy(temp->val, val, list->ele_size);
    temp->next = NULL;

    if (list->tail == NULL) {
        list->head = temp;
        list->tail = temp;
    } else {
        list->tail->next = temp;
        list->tail = temp;
    }
    ++(list->len);
    return 0;
}

void* linked_list_remove_first(struct linked_list_t* list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    struct list_node* first = list->head;
    void* val = malloc(sizeof(list->ele_size));
    if (val == NULL) {
        return NULL;
    }
    memcpy(val, first->val, list->ele_size);

    list->head = first->next;
    if (list->tail == first) {
        list->tail = NULL;
    }
    free(first);
    --(list->len);
    return val;

}

void* linked_list_remove_last(struct linked_list_t* list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    struct list_node* last = list->tail;
    void* val = malloc(sizeof(list->ele_size));
    if (val == NULL) {
        return NULL;
    }
    memcpy(val, last->val, list->ele_size);

    if (list->head == last) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        struct list_node* itr = list->head;
        while (itr->next != last) {
            itr = itr->next;
        }
        list->tail = itr;
    }
    free(last);
    --(list->len);
    return val;
}

void* linked_list_remove_ith(struct linked_list_t* list, size_t index) {
    if (index >= list->len) {
        return NULL;
    }
    if (index == 0) {
        return linked_list_remove_first(list);
    }
    if (index == (list->len - 1)) {
        return linked_list_remove_last(list);
    }
    struct list_node* fast;
    struct list_node* slow = list->head;
    int i = 1;
    while (i < index) {
        slow = slow->next;
//		fast = fast->next;
        ++i;
    }
    fast = slow->next;
    void* val = malloc(sizeof(list->ele_size));
    if (val == NULL) {
        return NULL;
    }
    memcpy(val, fast->val, list->ele_size);

    slow->next = fast->next;
    free(fast);
    --(list->len);
    return val;

}

size_t linked_list_len(struct linked_list_t* list) {
    if (list == NULL) {
        return 0;
    }
    return list->len;
}

int fibonacci(int i) {
    if (i < 1) {
        return -1;
    } else if (i < 3) {
        return 1;
    }
    int n_2 = 1, n_1 = 1;
    int j = 2, n;
    while (j < i) {
        n = n_2 + n_1;
        n_2 = n_1;
        n_1 = n;
        ++j;
    }
    return n;
}

struct wd_queue {
    size_t ele_size;
    size_t head;
    size_t tail;
    size_t cap;
    unsigned char* array;
};

struct wd_queue* wd_create_queue(size_t ele_size) {
    struct wd_queue* queue = (struct wd_queue* )malloc(sizeof(*queue));
    if (queue != NULL) {
        int cap = 4;
        queue->ele_size = ele_size;
        queue->head = 0;
        queue->tail = 0;
        queue->cap = cap;
        queue->array = malloc(ele_size * cap);
    }
    return queue;
}

int wd_enqueue(struct wd_queue* queue, void* data) {
    if (queue == NULL || data == NULL) {
        return -1;
    }
    if (queue->tail == queue->cap) {
        queue->cap <<= 1;
        queue->array = realloc(queue->array, queue->cap * queue->ele_size);
        if (queue->array == NULL) {
            return -2;
        }
    }
    memcpy(queue->array + (queue->tail)++ * queue->ele_size, data, queue->ele_size);
    return 0;
}

int wd_dequeue(struct wd_queue* queue, void* data) {
    if (queue == NULL || data == NULL) {
        return -1;
    }
    if (queue->head == queue->tail) {
        return -3;
    }
    size_t ele_size = queue->ele_size;
    unsigned char* array = queue->array;
    memcpy(data, array + (queue->head)++ * ele_size, ele_size);
    if ((queue->head  << 1) > queue->cap) {
        memcpy(array, array + queue->head * ele_size, ele_size * (queue->tail - queue->head));
        (queue->cap) >>= 1;
        queue->array = realloc(array, queue->cap * ele_size);
        queue->tail -= queue->head;
        queue->head = 0;
    }
    if (queue->head == queue->tail) { // queue is empty
        queue->head = 0;
        queue->tail = 0;
    }
    return 0;
}

int wd_queue_size(struct wd_queue* queue) {
    if (queue == NULL) {
        return -1;
    }
    return queue->tail - queue->head;
}

struct wd_deque {
    size_t ele_size;
    size_t head;
    size_t tail;
    size_t base;
    size_t cap;
    unsigned char* array;
};

struct wd_deque* wd_create_deque(size_t ele_size) {
    struct wd_deque* deque = (struct wd_deque* )malloc(sizeof(*deque));
    if (deque == NULL) {
        return NULL;
    }
    size_t cap = 4;
    deque->ele_size = ele_size;
    deque->head = cap >> 1;
    deque->tail = deque->head;
    deque->base = deque->head;
    deque->cap = cap;
    deque->array = malloc(cap * ele_size);
    if (deque->array == NULL) {
        return NULL;
    }
    return deque;
}

int wd_deque_add_last(struct wd_deque* deque, void* data) {
    if (deque == NULL || data == NULL) {
        return -1;
    }
    size_t ele_size = deque->ele_size;
    if (deque->tail == deque->cap) {
        deque->cap += deque->tail - deque->base;
        deque->array = realloc(deque->array, deque->cap * ele_size);
        if (deque->array == NULL) {
            return -2;
        }
    }
    memcpy(deque->array + (deque->tail)++ * ele_size, data, ele_size);
    return 0;
}

int wd_deque_remove_last(struct wd_deque* deque, void* data) {
    if (deque == NULL || data == NULL) {
        return -1;
    }
    if (deque->head == deque->tail) {
        return -3;
    }
    size_t ele_size = deque->ele_size;
    memcpy(data, deque->array + (--(deque->tail)) * ele_size, ele_size);
    if ( ( (deque->cap - deque->tail) << 1) > deque->cap ) {
        deque->cap -= (deque->cap - deque->tail) >> 1;
        deque->array = realloc(deque->array, deque->cap * ele_size);
        if (deque->array == NULL) {
            return -2;
        }
    }
    return 0;
}

int wd_deque_add_first(struct wd_deque* deque, void* data) {
    if (deque == NULL || data == NULL) {
        return -1;
    }
    size_t ele_size = deque->ele_size;
    if (deque->head == 0) {
        size_t extra = deque->base - deque->head;
        unsigned char* new_array = malloc((deque->cap + extra) * ele_size);
        if (new_array == NULL) {
            return -2;
        }
        memcpy(new_array + extra * ele_size, deque->array, (deque->tail - deque->head) * ele_size);
        deque->array = new_array;
        deque->head = extra;
        deque->base += extra;
        deque->tail += extra;
        deque->cap += extra;
    }
    memcpy(deque->array + --(deque->head) * ele_size, data, ele_size);
    return 0;
}

int wd_deque_remove_first(struct wd_deque* deque, void* data) {
    if (deque == NULL || data == NULL) {
        return -1;
    }
    if (deque->head == deque->tail) {
        return -3;
    }
    size_t ele_size = deque->ele_size;
    memcpy(data, deque->array + (deque->head)++ * ele_size, ele_size);
    if ((deque->head << 1) > deque->cap) {
        size_t surplus = deque->head >> 1;
        unsigned char* new_array = malloc((deque->cap - surplus) * ele_size);
        if (new_array == NULL) {
            return -2;
        }
        memcpy(new_array + (deque->head - surplus) * ele_size, deque->array + deque->head * ele_size, (deque->tail - deque->head) * ele_size);
        deque->cap -= surplus;
        deque->head -= surplus;
        deque->tail -= surplus;
        deque->base -= surplus;
        deque->array = new_array;
    }
    return 0;
}

int wd_deque_size(struct wd_deque* deque) {
    return deque == NULL ? -1 : deque->tail - deque->head;
}

struct wd_heap {
    size_t ele_size;
    size_t len;
    size_t cap;
    unsigned char* array;
    int (*compare)(const void* a, const void* b);
};

struct wd_heap* wd_create_heap(size_t ele_size, int (*compare)(const void* a, const void* b)) {
    if (compare == NULL) {
        return NULL;
    }
    struct wd_heap* heap = (struct wd_heap* )malloc(sizeof(*heap));
    if (heap == NULL) {
        return NULL;
    }
    size_t cap = 4;
    heap->ele_size = ele_size;
    heap->len = 0;
    heap->cap = cap;
    heap->array = malloc(ele_size * cap);
    heap->compare = compare;
    return heap;

}

void wd_max_heapify(unsigned char* data, size_t i, size_t len, size_t ele_size, int (*compare)(const void* a, const void* b)) {
    void* left = NULL;
    void* right = NULL;
    void* me = malloc(ele_size);
    memcpy(me, data + i * ele_size, ele_size);
    void* big = me;
    size_t left_index = i << 1;
    size_t right_index = left_index + 1;
    size_t big_index = i;
    if (left_index < len) {
        left = malloc(ele_size);
        memcpy(left, data + left_index * ele_size, ele_size);
        if (compare(me, left) < 0) {
            big_index = left_index;
            big = left;
        }
    }
    if (right_index < len) {
        right = malloc(ele_size);
        memcpy(right, data + right_index * ele_size, ele_size);
        if (compare(big, right) < 0) {
            big_index = right_index;
            big = right;
        }
    }
    if (big != me) {
        memcpy(data + i * ele_size, big, ele_size);
        memcpy(data + big_index * ele_size, me, ele_size);
        wd_max_heapify(data, big_index, len, ele_size, compare);
    }
    if (left) {
        free(left);
    }
    if (right) {
        free(right);
    }
    free(me);
}

int wd_heap_peak(struct wd_heap* heap, void* data) {
    if (heap == NULL || data == NULL) {
        return -1;
    }
    memcpy(data, heap->array, heap->ele_size);
    return 0;
}

int wd_heap_pop(struct wd_heap* heap, void* data) {
    if (heap == NULL || data == NULL) {
        return -1;
    }
    size_t ele_size = heap->ele_size;
    unsigned char* array = heap->array;
    memcpy(data, array, ele_size);
    memcpy(array, array + --(heap->len) * ele_size, ele_size);
    wd_max_heapify(array, 0, heap->len, ele_size, heap->compare);
    if ((heap->len << 1) < heap->cap) {
        heap->cap >>= 1;
        heap->array = realloc(array, heap->cap * ele_size);
        if (heap->array == NULL) {
            return -2;
        }
    }
    return 0;
}

int wd_heap_insert(struct wd_heap* heap, void* data) {
    if (heap == NULL || data == NULL) {
        return -1;
    }
    size_t ele_size = heap->ele_size;
    if (heap->len == heap->cap) {
        heap->cap <<= 1;
        heap->array = realloc(heap->array, heap->cap * ele_size);
        if (heap->array == NULL) {
            return -2;
        }
    }
    unsigned char* array = heap->array;
    memcpy(array + heap->len * ele_size, data, ele_size);

    // replace data with its parent until its parent is no less than it
    int (*compare)(const void*, const void*);
    compare = heap->compare;
    size_t my_index = heap->len;
    size_t parent_index = my_index >> 1;
    void* me = malloc(ele_size);
    void* parent = malloc(ele_size);
    memcpy(parent, array + parent_index * ele_size, ele_size);
    memcpy(me, array + my_index * ele_size, ele_size);
    while (/*parent_index >= 0 &&*/ compare(parent, me) < 0 ) {
        memcpy(array + parent_index * ele_size, me, ele_size);
        memcpy(array + my_index * ele_size, parent, ele_size);
        my_index = parent_index;
        parent_index = my_index >> 1;
        me = parent;
        memcpy(parent, array + parent_index * ele_size, ele_size);
    }
    heap->len += 1;
    return 0;
}

struct wd_heap* wd_array_to_heap(void* data, size_t len, size_t ele_size, int (*compare)(const void* a, const void* b)) {
    if (data == NULL || len < 1 || ele_size < 1 || compare == NULL) {
        return NULL;
    }
    unsigned char* copy = malloc(len * ele_size);
    memcpy(copy, data, len * ele_size);
    size_t i;
    for (i = (len - 1) >> 1; i > 0; --i) {
        wd_max_heapify(copy, i, len, ele_size, compare);
    }
    wd_max_heapify(copy, 0, len, ele_size, compare);
    struct wd_heap* heap = (struct wd_heap* )malloc(sizeof(*heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->ele_size = ele_size;
    heap->len = len;
    heap->cap = len;
    heap->array = copy;
    heap->compare = compare;
    return heap;
}

size_t wd_heap_size(struct wd_heap* heap) {
    if (heap == NULL) {
        return 0;
    }
    return heap->len;
}