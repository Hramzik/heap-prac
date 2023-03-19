#ifndef TESTS_CPP_INCLUDED
#define TESTS_CPP_INCLUDED
//--------------------------------------------------


#include "../hpp/common.hpp"


size_t sort_time ( Return_code (sort_func) (Array*, Sort_info*), Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Array* my_array = array_dup (array);


    //-----------------------
    clock_t start = clock (); //sleep (1);

    sort_func (my_array, info); // array_print (my_array);

    clock_t end = clock ();
    //-----------------------


    array_dtor (my_array);


    return (end - start) * 1000 / CLOCKS_PER_SEC; // ms
}


size_t sort_avg_time ( Return_code (sort_func) (Array*, Sort_info*), Array* array, Sort_info* info) {

    if (!array) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    Sort_info do_print   = *info;
    Sort_info dont_print = *info; dont_print.print = false;


    size_t time1 = sort_time (sort_func, array, &dont_print) / 5;
    size_t time2 = sort_time (sort_func, array, &dont_print) / 5;
    size_t time3 = sort_time (sort_func, array, &dont_print) / 5;
    size_t time4 = sort_time (sort_func, array, &dont_print) / 5;
    size_t time5 = sort_time (sort_func, array, &do_print)   / 5;

    return time1 + time2 + time3 + time4 + time5;
}


Return_code sorts_test (size_t start_size, size_t max_size, size_t step_size, Sort_info* info) {

    for (size_t n = start_size; n < max_size; n += step_size) {

        sorts_one_test (n, info);
    }


    return SUCCESS;
}


//--------------------------------------------------
#define CREATE_INFO(n) Sort_info* info##n = sort_info_dup (info, n)
#define KILL_INFO(n)   sort_info_dtor (info##n);
//--------------------------------------------------

Return_code sorts_one_test (size_t size, Sort_info* info) {

    Array* array = array_generate (size);


    CREATE_INFO (5);
    CREATE_INFO (10);
    CREATE_INFO (25);
    CREATE_INFO (100);
    CREATE_INFO (200);
    CREATE_INFO (300);
    CREATE_INFO (400);
    CREATE_INFO (500);
    CREATE_INFO (1000);

    write ("sheap5",    size, sort_avg_time (sheap_sort, array, info5));
    write ("sheap10",   size, sort_avg_time (sheap_sort, array, info10));
    write ("sheap25",   size, sort_avg_time (sheap_sort, array, info25));
    write ("sheap100",  size, sort_avg_time (sheap_sort, array, info100));
    write ("sheap200",  size, sort_avg_time (sheap_sort, array, info200));
    write ("sheap300",  size, sort_avg_time (sheap_sort, array, info300));
    write ("sheap400",  size, sort_avg_time (sheap_sort, array, info400));
    write ("sheap500",  size, sort_avg_time (sheap_sort, array, info500));
    write ("sheap1000", size, sort_avg_time (sheap_sort, array, info1000));


    array_dtor (array);


    KILL_INFO (5);
    KILL_INFO (10);
    KILL_INFO (25);
    KILL_INFO (100);
    KILL_INFO (200);
    KILL_INFO (300);
    KILL_INFO (400);
    KILL_INFO (500);
    KILL_INFO (1000);


    return SUCCESS;
}

//--------------------------------------------------
#undef CREATE_INFO
#undef KILL_INFO
//--------------------------------------------------


Return_code write (const char* name, size_t size, size_t result) {

    if (!name) { LOG_ERROR (BAD_ARGS); return BAD_ARGS; }


    char file_name [strlen (name) + 5 + 5] = "";
    strcat (file_name, "work/");
    strcat (file_name, name);
    strcat (file_name, ".txt");
    FILE* file = fopen (file_name, "a");


    fprintf (file, "%-8zd, %-8zd\n", size, result);


    fclose (file);


    return SUCCESS;
}


//--------------------------------------------------
#endif