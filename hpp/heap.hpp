#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED
//--------------------------------------------------


#include "common.hpp"


typedef struct Heap {

    int* buffer;
    size_t size;
    size_t capacity;

} Heap; const size_t HEAP_SIZE = sizeof (Heap);


Heap*       heap_ctor (size_t capacity);
Return_code heap_dtor (Heap* heap);
Return_code build_heap_dtor (Heap* heap);
Return_code sift_down   (Heap* heap,  size_t i);
Return_code sift_up     (Heap* heap,  size_t i);
Heap*       heap_build  (Array* array);
Return_code get_min     (Heap* heap, int* buffer);
Return_code pop_min     (Heap* heap, int* buffer);
Return_code heap_resize (Heap* heap);
Return_code heap_push   (Heap* heap, int value);
Return_code heap_sort   (Array* array, Sort_info* info);


//--------------------------------------------------
#endif