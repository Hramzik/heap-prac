#ifndef SHEAP_HPP_INCLUDED
#define SHEAP_HPP_INCLUDED
//--------------------------------------------------


#include "common.hpp"


typedef struct Node {

    int  value;
    size_t key;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct hHeap {

    Node*  buffer;
    size_t size;
    size_t capacity;

} hHeap; const size_t HHEAP_SIZE = sizeof (hHeap);


typedef struct sHeap {

    int*   buffer;
    size_t size;
    size_t capacity;

    size_t k;

    hHeap** minimums; // плохое название, но вообщем это массив куч сыновей элементов

} sHeap; const size_t SHEAP_SIZE = sizeof (sHeap);


Return_code build_heap_dtor (sHeap* heap);
Return_code sift_down       (sHeap* heap,  size_t n);
Return_code sift_up         (sHeap* heap,  size_t n);
sHeap*      sheap_build     (Array* array, size_t k);
Return_code get_min         (sHeap* heap, int* buffer);
Return_code pop_min         (sHeap* heap, int* buffer);
Return_code sheap_sort      (Array* array, Sort_info* info);


Return_code heap_dtor   (hHeap* heap);
Return_code sift_down   (hHeap* heap, size_t n, bool swap_subheaps = true);
Return_code sift_up     (hHeap* heap, size_t n);
Return_code hheap_build (sHeap* heap, size_t n);
Return_code get_min     (hHeap* heap, size_t* buffer);
Return_code pop_min     (hHeap* heap, Node* buffer);
Return_code heap_push   (hHeap* heap, Node  value);
Return_code heap_print      (hHeap* heap);


Return_code swap_hheap_ptr (hHeap** p1,    hHeap** p2);
Return_code swap_node      (Node*   node1, Node*   node2);


//--------------------------------------------------
#endif