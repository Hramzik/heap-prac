

#include "../hpp/main.hpp"


int main (void) {


    Sort_info info = { .reversed = false, .print = false, .k = 0 }; // partition ни на что не влияет, он задается позже, как и k


    // sorts_test (17, 18, 1, &info);


    sorts_test (100'000, 10'000'000, 100'000, &info);


    printf ("\ngoodbye!\n");


    return 0;
}
