#ifndef SHEAP_CPP_INCLUDED
#define SHEAP_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/sheap.hpp"


Return_code build_heap_dtor (sHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i < heap->capacity; i++) {

        heap_dtor (heap->minimums [i]);
    }

    free (heap->minimums);


    free (heap);


    return SUCCESS;
}


sHeap* sheap_build (Array* array, size_t k) {

    sHeap* heap = (sHeap*) calloc (SHEAP_SIZE, 1);


    heap->buffer   = array->elements;
    heap->capacity = array->size;
    heap->size     = array->size;
    heap->k        = k;


    size_t last_sifted = array->size / k; // построение основной кучи
    for (size_t i = 0; i <= last_sifted; i++) {

        sift_down (heap, last_sifted - i, false); printf ("sifted %zd\n", last_sifted - i);
    }


    heap->minimums = (hHeap**) calloc (heap->capacity, sizeof (hHeap*)); // посторение sub-куч
    for (size_t i = 0; i < heap->capacity; i++) {

        hheap_build (heap, i); // heap_print (heap->minimums [i]);
    }


    return heap;
}


Return_code sift_down (sHeap* heap, size_t n, bool swap_subheaps) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (SON (n, 1))) { printf ("current - %zd ", n);

        get_min (heap->minimums [n], &min_son); // heap_print (heap->minimums [n]); printf ("minimum: %d\n", HEAP (min_son));


        if (HEAP (n) <= HEAP (min_son)) { break; }


        if (swap_subheaps) {

            pop_min   (heap->minimums [n], nullptr);
            Node new_node = { .value = HEAP (n), .key = min_son };
            heap_push (heap->minimums [n], new_node);
            swap_hheap_ptr (&MINIMUM (n), &MINIMUM (min_son));
        }


        swap_int       (&HEAP    (n), &HEAP    (min_son));
        n = min_son;
    } printf ("end\n");


    return SUCCESS;
}


Return_code sift_up (sHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (n && HEAP (n) < HEAP (kPARENT (n))) {

        pop_min   (MINIMUM (kPARENT (n)), nullptr); // у родителя
        Node new_node = { .value = HEAP (kPARENT (n)), .key = n };
        heap_push (MINIMUM (kPARENT (n)), new_node);


        swap_int      (&HEAP (n),     &HEAP    (kPARENT (n)));
        swap_hheap_ptr (&MINIMUM (n), &MINIMUM (kPARENT (n)));

        n = kPARENT (n);
    }


    return SUCCESS;
}


Return_code get_min (sHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    return SUCCESS;
}


Return_code pop_min (sHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0);


    HEAP (0) = HEAP (heap->size - 1);
    MINIMUM (0)
    heap->size -= 1;


    sift_down (heap, 0);


    return SUCCESS;
}


Return_code sheap_sort (Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!info)  { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Array* temp = array_dup (array);
    sHeap* heap  = sheap_build (temp, info->k);


    for (size_t i = 0; i < array->size; i++) {

        pop_min (heap, &array->elements [i]);
    }


    build_heap_dtor (heap);
    array_dtor      (temp);


    if (info->print) { array_print (array); }


    return SUCCESS;
}

Return_code heap_print (hHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("hheap: ");
    for (size_t i = 0; i < heap->size; i++) {

        printf ("%i ", heap->buffer [i].value);
    }
    printf ("\n");


    return SUCCESS;
}


//--------------------------------------------------
#endif