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


    heap->minimums [n]->buffer   = (hNode*) calloc (heap->k, HNODE_SIZE);
    heap->minimums [n]->capacity = heap->k;
    heap->minimums [n]->size     = 0;


    size_t first_son = heap->k * n + 1; //first son
    size_t cur_son = first_son;

    while (IN_HEAP (cur_son) && (cur_son < first_son + heap->k)) {

        hNode cur_node = { .value = SHEAP (cur_son), .key = cur_son };
        heap_push (heap->minimums [n], cur_node, heap->buffer);

        cur_son += 1;
    }


    return SUCCESS;
}


Return_code sift_down (hHeap* heap, size_t n, sNode* sbuffer) { // sbuffer - массив из большой sкучи

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    size_t min_son = 0;
    while (IN_HEAP (LEFT (n))) {

        min_son = LEFT (n);
        if (IN_HEAP (RIGHT (n)) && HEAP (RIGHT (n)).value < HEAP (LEFT (n)).value) { min_son = RIGHT (n); }


        if (HEAP (n).value <= HEAP (min_son).value) { break; }


        if (sbuffer) {

            sbuffer [HHEAP (n)]      .child_index = min_son;
            sbuffer [HHEAP (min_son)].child_index = n;
        }


        swap_hnode (&HEAP (n), &HEAP (min_son));


        n = min_son;
    }


    return SUCCESS;
}


Return_code sift_up (hHeap* heap, size_t n, sNode* sbuffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }



    while (n && HEAP (n).value < HEAP (PARENT (n)).value) {

        if (sbuffer) {

            sbuffer [HHEAP (n)]         .child_index = PARENT (n);
            sbuffer [HHEAP (PARENT (n))].child_index = n;
        }


        swap_hnode (&HEAP (n), &HEAP (PARENT (n)));
        n = PARENT (n);
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


Return_code pop_min (hHeap* heap, hNode* answer, sNode* sbuffer) {

    if (!heap)         { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    if (answer) { *answer = HEAP (0); }


    HEAP (0)                          = HEAP (heap->size - 1);
    sbuffer [HHEAP (0)].child_index = 0; // пропустил эту строчку, дебажил 2 часа
    heap->size -= 1;


    sift_down (heap, 0, sbuffer);


    return SUCCESS;
}


Return_code heap_push (hHeap* heap, hNode value, sNode* sbuffer) {

    if (!heap)                        { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!heap->buffer)                { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!sbuffer)                     { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (heap->size == heap->capacity) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }

    // if (heap->size == heap->capacity) { heap_resize (heap); } всегда один размер


    heap->size += 1;


    HEAP    (heap->size - 1) = value;
    sbuffer [value.key].child_index = heap->size - 1;


    sift_up (heap, heap->size - 1, sbuffer);


    return SUCCESS;
}

Return_code heap_pop (hHeap* heap, size_t index, sNode* sbuffer) {

    if (!heap) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    int cur_min                = heap->buffer [0].value;
    heap->buffer [index].value = cur_min - 1; // может быть бага, если это INT_MIN


    sift_up (heap, index,   sbuffer);
    pop_min (heap, nullptr, sbuffer);


    return SUCCESS;
}


/*
Return_code swap_hheap_ptr (hHeap** p1, hHeap** p2) {

    if (!p1) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!p2) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    hHeap* temp = *p1;
    *p1 = *p2;
    *p2 = temp;


    return SUCCESS;
}
*/

Return_code swap_hnode (hNode* node1, hNode* node2) {

    if (!node1) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }
    if (!node2) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    hNode temp = *node1;
    *node1     = *node2;
    *node2     =  temp;


    return SUCCESS;
}


//--------------------------------------------------
#endif