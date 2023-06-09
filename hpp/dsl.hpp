#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED
//--------------------------------------------------
#define LEFT(i)        (2*(i) + 1)
#define RIGHT(i)       (2*(i) + 2)
#define IN_HEAP(i)     ((i) < heap->size)
#define HEAP(i)        (heap->buffer [i])
#define SHEAP(i)       (heap->buffer [i].value)
#define HHEAP(i)       (heap->buffer [i].key)
#define CHILD_INDEX(i) (heap->buffer [i].child_index)
#define SON(n, i)      ((heap->k)*(n) + (i))
#define PARENT(i)      (((i) - 1) / 2)
#define KPARENT(n)     (((n) - 1) / (heap->k))
#define MINIMUM(n)     (heap->minimums [n])
//--------------------------------------------------
#endif