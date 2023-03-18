#ifndef HHEAP_CPP_INCLUDED
#define HHEAP_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/sheap.hpp"


Return_code heap_dtor (hHeap* heap) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    free (heap->buffer);
    free (heap);


    return SUCCESS;
}


Return_code hheap_build (sHeap* heap, size_t n) {

    heap->minimums [n] = (hHeap*) calloc (1, HHEAP_SIZE);


    heap->minimums [n]->buffer   = (Node*) calloc (heap->k, NODE_SIZE);
    heap->minimums [n]->capacity = heap->k;
    heap->minimums [n]->size     = 0;


    size_t first_son = heap->k * n + 1; //first son
    size_t cur_son = first_son;
    while (IN_HEAP (cur_son) && (cur_son < first_son + heap->k)) {

        heap_push (heap->minimums [n], { .value = heap->buffer [cur_son], .key = cur_son });
        cur_son += 1;
    }


    return SUCCESS;
}


Return_code sift_down (hHeap* heap, size_t n) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (LEFT (n))) {

        min_son = LEFT (n);
        if (IN_HEAP (RIGHT (n)) && HEAP (RIGHT (n)).value < HEAP (LEFT (n)).value) { min_son = RIGHT (n); }


        if (HEAP (n).value <= HEAP (min_son).value) { break; }


        swap_node (&HEAP (n), &HEAP (min_son));
        n = min_son;
    }


    return SUCCESS;
}


Return_code sift_up (hHeap* heap, size_t i) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (i && HEAP (i).value < HEAP (PARENT (i)).value) {

        swap_node (&HEAP (i), &HEAP (PARENT (i)));
        i = PARENT (i);
    }


    return SUCCESS;
}


Return_code get_min (hHeap* heap, size_t* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!buffer)       { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->size)   { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    *buffer = HEAP (0).key;


    return SUCCESS;
}


Return_code pop_min (hHeap* heap, Node* buffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (buffer) { *buffer = HEAP (0); }


    HEAP (0) = HEAP (heap->size - 1);
    heap->size -= 1;


    sift_down (heap, 0);


    return SUCCESS;
}


Return_code heap_push (hHeap* heap, Node value) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    // if (heap->size == heap->capacity) { heap_resize (heap); } всегда один размер


    heap->size += 1;


    HEAP (heap->size - 1) = value;


    sift_up (heap, heap->size - 1);


    return SUCCESS;
}


Return_code swap_hheap_ptr (hHeap** p1, hHeap** p2) {

    if (!p1) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!p2) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    hHeap* temp = *p1;
    *p1 = *p2;
    *p2 = temp;


    return SUCCESS;
}


Return_code swap_node (Node* node1, Node* node2) {

    if (!node1) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!node2) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Node temp = *node1;
    *node1 = *node2;
    *node2 = temp;


    return SUCCESS;
}


//--------------------------------------------------
#endif