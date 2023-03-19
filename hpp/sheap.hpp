#ifndef SHEAP_HPP_INCLUDED
#define SHEAP_HPP_INCLUDED
//--------------------------------------------------


#include "common.hpp"


typedef struct hNode {

    int  value;
    size_t key;

} hNode; const size_t HNODE_SIZE = sizeof (hNode);


typedef struct hHeap {

    hNode*  buffer;
    size_t size;
    size_t capacity;

} hHeap; const size_t HHEAP_SIZE = sizeof (hHeap);


typedef struct sNode {

    int    value;
    size_t child_index;

} sNode; const size_t SNODE_SIZE = sizeof (sNode);


typedef struct sHeap {

    sNode* buffer;
    size_t size;
    size_t capacity;

    size_t k;

    hHeap** minimums; // плохое название, но вообщем это массив куч сыновей элементов

} sHeap; const size_t SHEAP_SIZE = sizeof (sHeap);


sHeap*      sheap_build                   (Array* array, size_t k);
Return_code heap_dtor                     (sHeap* heap);
Return_code heap_print                    (sHeap* heap);
Return_code child_indexes_print           (sHeap* heap);
Return_code heap_dump                     (sHeap* heap);
Return_code sift_down                     (sHeap* heap,  size_t n);
Return_code sift_up                       (sHeap* heap,  size_t n);
Return_code swap_value_in_parents_subheap (sHeap* heap, size_t my_index, int new_value);
Return_code get_min                       (sHeap* heap, int* buffer);
Return_code pop_min                       (sHeap* heap, int* buffer);
Return_code sheap_sort                    (Array* array, Sort_info* info);


Return_code heap_dtor   (hHeap* heap);
Return_code sift_down   (hHeap* heap, size_t n, sNode* sbuffer = nullptr);
Return_code sift_up     (hHeap* heap, size_t n, sNode* sbuffer = nullptr);
Return_code hheap_build (sHeap* heap, size_t n);
Return_code get_min     (hHeap* heap, size_t* buffer);
Return_code pop_min     (hHeap* heap, hNode* answer, sNode* buffer);
Return_code heap_push   (hHeap* heap, hNode  value,  sNode* sbuffer = nullptr);
Return_code heap_pop    (hHeap* heap, size_t index, sNode* buffer);
Return_code heap_print  (hHeap* heap, size_t index);

Return_code swap_hheap_ptr (hHeap** p1,    hHeap** p2);
Return_code swap_hnode     (hNode*   node1, hNode*   node2);


//--------------------------------------------------
#endif