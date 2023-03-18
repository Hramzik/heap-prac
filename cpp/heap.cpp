#ifndef HEAP_CPP_INCLUDED
#define HEAP_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/heap.hpp"


Heap* heap_ctor (size_t capacity) {

    Heap* heap = (Heap*) calloc (HEAP_SIZE, 1);


    heap->buffer = (int*) calloc (capacity * INT_SIZE, 1);
    heap->capacity = capacity;

    heap->size = 0;


    return heap;
}


Return_code heap_dtor (Heap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (heap->buffer);
    free (heap);


    return SUCCESS;
}

Return_code build_heap_dtor (Heap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (heap);


    return SUCCESS;
}


Heap* heap_build (Array* array) {

    Heap* heap = (Heap*) calloc (HEAP_SIZE, 1);


    heap->buffer   = array->elements;
    heap->capacity = array->size;
    heap->size     = array->size;


    size_t last_sifted = array->size / 2;
    for (size_t i = 0; i <= last_sifted; i++) {

        sift_down (heap, last_sifted - i);
    }


    return heap;
}


//--------------------------------------------------
#define IN_HEAP(i) ((i) < heap->size)
#define    HEAP(i) (heap->buffer [i])
//--------------------------------------------------

Return_code sift_down (Heap* heap, size_t i) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (LEFT (i))) {

        min_son = LEFT (i);
        if (IN_HEAP (RIGHT (i)) && HEAP (RIGHT (i)) < HEAP (LEFT (i))) { min_son = RIGHT (i); }


        if (HEAP (i) <= HEAP (min_son)) { break; }


        swap_int (&HEAP (i), &HEAP (min_son));
        i = min_son;
    }


    return SUCCESS;
}


Return_code sift_up (Heap* heap, size_t i) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (i && HEAP (i) < HEAP (PARENT (i))) {

        swap_int (&HEAP (i), &HEAP (PARENT (i)));
        i = PARENT (i);
    }


    return SUCCESS;
}


Return_code get_min (Heap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    return SUCCESS;
}


Return_code pop_min (Heap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    HEAP (0) = HEAP (heap->size - 1);
    heap->size -= 1;


    sift_down (heap, 0);


    return SUCCESS;
}


Return_code heap_resize (Heap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t new_capacity = heap->capacity * 2 + 1;
    heap->capacity = new_capacity;


    heap->buffer = (int*) realloc (heap->buffer, new_capacity * INT_SIZE);


    return SUCCESS;
}


Return_code heap_push (Heap* heap, int value) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (heap->size == heap->capacity) { heap_resize (heap); }


    heap->size += 1;


    HEAP (heap->size - 1) = value;


    sift_up (heap, heap->size - 1);


    return SUCCESS;
}


Return_code heap_sort (Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!info)  { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Array* temp = array_dup (array);
    Heap* heap  = heap_build (temp);


    for (size_t i = 0; i < array->size; i++) {

        pop_min (heap, &array->elements [i]);
    }


    build_heap_dtor (heap);
    array_dtor (temp);


    if (info->print) { array_print (array); }


    return SUCCESS;
}


//--------------------------------------------------
#endif