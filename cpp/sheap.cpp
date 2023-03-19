#ifndef SHEAP_CPP_INCLUDED
#define SHEAP_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/sheap.hpp"


Return_code heap_dtor (sHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    for (size_t i = 0; i <= ((heap->capacity - 2) / heap->k); i++) {

        heap_dtor (heap->minimums [i]);
    }

    free (heap->minimums);


    free (heap->buffer);


    free (heap);


    return SUCCESS;
}


sHeap* sheap_build (Array* array, size_t k) {

    sHeap* heap = (sHeap*) calloc (1, SHEAP_SIZE);
    heap->size     = array->size;
    heap->capacity = array->size;
    heap->k        = k;


    heap->buffer = (sNode*) calloc (heap->capacity, SNODE_SIZE);
    for (size_t i = 0; i < heap->capacity; i++) {

        sNode cur_node = { .value = array->elements [i], .child_index = 0 };
        heap->buffer [i] = cur_node;
    }


    heap->minimums = (hHeap**) calloc (heap->capacity, sizeof (hHeap*)); // посторение sub-куч
    for (size_t i = 0; i <= ((heap->capacity - 2) / heap->k); i++) {

        hheap_build (heap, i);
    }


    size_t last_sifted = heap->capacity / k; // построение основной кучи
    for (size_t i = 0; i <= last_sifted; i++) {

        sift_down (heap, last_sifted - i);
    }


    return heap;
}


Return_code sift_down (sHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (SON (n, 1))) {

        get_min (heap->minimums [n], &min_son);


        if (SHEAP (n) <= SHEAP (min_son)) { break; }


        if (n > 0) {

            swap_value_in_parents_subheap (heap, n, SHEAP (min_son));
        }


        pop_min   (heap->minimums [n], nullptr, heap->buffer);
        hNode new_node = { .value = SHEAP (n), .key = min_son };
        heap_push (heap->minimums [n], new_node, heap->buffer);


        swap_int (&SHEAP (n), &SHEAP (min_son)); // sub-кучи менять не надо, мы уже изменили там нужную величину
        n = min_son;

    }


    return SUCCESS;
}


Return_code swap_value_in_parents_subheap (sHeap* heap, size_t my_index, int new_value) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    hHeap* hheap       = MINIMUM (KPARENT (my_index));
    size_t child_index = CHILD_INDEX (my_index);


    int cur_min = hheap->buffer [0].value;


    hheap->buffer [child_index].value = cur_min - 1; // может быть бага, если это INT_MIN
    sift_up (hheap, child_index, heap->buffer);      // должен оказаться наверху


    hheap->buffer [0].value = new_value; // тут написал не то, дебажил час
    sift_down (hheap, 0, heap->buffer);


    return SUCCESS;
}

/*
Return_code sift_up (sHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (n && HEAP (n) < HEAP (KPARENT (n))) {

        pop_min   (MINIMUM (KPARENT (n)), nullptr); // у родителя
        hNode new_node = { .value = HEAP (KPARENT (n)), .key = n };
        heap_push (MINIMUM (KPARENT (n)), new_node);


        swap_int      (&HEAP (n),     &HEAP    (KPARENT (n)));
        swap_hheap_ptr (&MINIMUM (n), &MINIMUM (KPARENT (n)));

        n = KPARENT (n);
    }


    return SUCCESS;
}
*/

Return_code get_min (sHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0).value;


    return SUCCESS;
}


Return_code pop_min (sHeap* heap, int* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0).value;


    HEAP (0) = HEAP (heap->size - 1);

    if (IN_HEAP (KPARENT (heap->size - 1))) { // то, что чела удалили, портит кучу его родителя

        hHeap* ruined_heap   = MINIMUM (KPARENT (heap->size - 1));
        size_t deleted_index = CHILD_INDEX (heap->size - 1);
        heap_pop (ruined_heap, deleted_index, heap->buffer);
    }

    heap->size -= 1;


    sift_down (heap, 0);


    return SUCCESS;
}


Return_code sheap_sort (Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!info)  { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Array* temp = array_dup   (array);
    sHeap* heap = sheap_build (temp, info->k);


    for (size_t i = 0; i < array->size; i++) {

        pop_min (heap, &array->elements [i]);
    }


    heap_dtor  (heap);
    array_dtor (temp);


    if (info->print) { array_print (array); }


    return SUCCESS;
}


Return_code heap_dump (sHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("\n");


    heap_print (heap);
    child_indexes_print (heap);
    for (size_t i = 0; i < heap->size; i++) {

        heap_print (MINIMUM (i), i);
    }


    return SUCCESS;
}


Return_code heap_print (sHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("sheap: ");
    for (size_t i = 0; i < heap->size; i++) {

        printf ("%6d ", heap->buffer [i].value);
    }
    printf ("\n");


    return SUCCESS;
}

Return_code child_indexes_print (sHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("CHind: ");
    for (size_t i = 0; i < heap->size; i++) {

        printf ("%6zd ", heap->buffer [i].child_index);
    }
    printf ("\n");


    return SUCCESS;
}


Return_code heap_print (hHeap* heap, size_t index) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    printf ("hheap%zd: ", index);
    for (size_t i = 0; i < heap->size; i++) {

        printf ("%d ", heap->buffer [i].value);
    }
    printf ("\n");


    return SUCCESS;
}


//--------------------------------------------------
#endif