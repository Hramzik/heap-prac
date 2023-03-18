#ifndef TESTS_HPP_INCLUDED
#define TESTS_HPP_INCLUDED
//--------------------------------------------------


#include "common.hpp"


size_t      sort_time      ( Return_code (sort_func) (Array*, Sort_info*), Array* array, Sort_info* info);
size_t      sort_avg_time  ( Return_code (sort_func) (Array*, Sort_info*), Array* array, Sort_info* info);
Return_code sorts_test     (size_t start_size, size_t max_size, size_t step_size,        Sort_info* info);
Return_code sorts_one_test (size_t size,                                                 Sort_info* info);

Return_code write (const char* name, size_t size, size_t result);


//--------------------------------------------------
#endif