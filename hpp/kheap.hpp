#ifndef KHEAP_HPP_INCLUDED
#define KHEAP_HPP_INCLUDED
//--------------------------------------------------


#include "common.hpp"


typedef struct kHeap {

    int*   buffer;
    size_t size;
    size_t capacity;

    size_t k;

} kHeap; const size_t KHEAP_SIZE = sizeof (kHeap);



kHeap*      kheap_ctor      (size_t capacity, size_t k);
Return_code heap_dtor       (kHeap* heap);
Return_code build_heap_dtor (kHeap* heap);
Return_code sift_down       (kHeap* heap,  size_t n);
Return_code sift_up         (kHeap* heap,  size_t n);
kHeap*      kheap_build     (Array* array, size_t k);
Return_code get_min         (kHeap* heap, int* buffer);
Return_code pop_min         (kHeap* heap, int* buffer);
Return_code heap_resize     (kHeap* heap);
Return_code heap_push       (kHeap* heap, int value);
Return_code kheap_sort      (Array* array, Sort_info* info);


//--------------------------------------------------
#endif