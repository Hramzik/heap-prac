#ifndef KHEAP_CPP_INCLUDED
#define KHEAP_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/kheap.hpp"


kHeap* kheap_ctor (size_t capacity, size_t k) {

    kHeap* heap = (kHeap*) calloc (KHEAP_SIZE, 1);


    heap->buffer = (int*) calloc (capacity * INT_SIZE, 1);
    heap->capacity = capacity;

    heap->size = 0;

    heap->k = k;


    return heap;
}


Return_code heap_dtor (kHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (heap->buffer);
    free (heap);


    return SUCCESS;
}

Return_code build_heap_dtor (kHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (heap);


    return SUCCESS;
}


kHeap* kheap_build (Array* array, size_t k) {

    kHeap* heap = (kHeap*) calloc (KHEAP_SIZE, 1);


    heap->buffer   = array->elements;
    heap->capacity = array->size;
    heap->size     = array->size;
    heap->k        = k;


    size_t last_sifted = array->size / k;
    for (size_t i = 0; i <= last_sifted; i++) {

        sift_down (heap, last_sifted - i);
    }


    return heap;
}


Return_code sift_down (kHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (n)) {

        min_son = SON (n, 1);
        for (size_t i = 2; i <= heap->k; i++) {

            size_t cur_son = SON (n, i);
            if (!IN_HEAP (cur_son)) { break; }

            if (HEAP (cur_son) < HEAP (min_son)) { min_son = cur_son; }
        }


        if (HEAP (n) <= HEAP (min_son)) { break; }


        swap_int (&HEAP (n), &HEAP (min_son));
        n = min_son;
    }


    return SUCCESS;
}


Return_code sift_up (kHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (n && HEAP (n) < HEAP (kPARENT (n))) {

        swap_int (&HEAP (n), &HEAP (kPARENT (n)));
        n = kPARENT (n);
    }


    return SUCCESS;
}


Return_code get_min (kHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    return SUCCESS;
}


Return_code pop_min (kHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    HEAP (0) = HEAP (heap->size - 1);
    heap->size -= 1;


    sift_down (heap, 0);


    return SUCCESS;
}


Return_code heap_resize (kHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    size_t new_capacity = heap->capacity * 2 + 1; // hard-coded
    heap->capacity = new_capacity;


    heap->buffer = (int*) realloc (heap->buffer, new_capacity * INT_SIZE);


    return SUCCESS;
}


Return_code heap_push (kHeap* heap, int value) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (heap->size == heap->capacity) { heap_resize (heap); }


    heap->size += 1;


    HEAP (heap->size - 1) = value;


    sift_up (heap, heap->size - 1);


    return SUCCESS;
}


Return_code kheap_sort (Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!info)  { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Array* temp = array_dup (array);
    kHeap* heap  = kheap_build (temp, info->k);


    for (size_t i = 0; i < array->size; i++) {

        pop_min (heap, &array->elements [i]);
    }


    build_heap_dtor (heap);
    array_dtor      (temp);


    if (info->print) { array_print (array); }


    return SUCCESS;
}


//--------------------------------------------------
#endif