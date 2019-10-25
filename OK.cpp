#include "error.h"
#include <iostream>
using namespace std;

void OK (int stat) {
    if (stat == STACK_NOT_FOUND_MR) {
        cerr << endl << "a null pointer is passed to my_realloc";
        exit(STACK_NOT_FOUND_MR);
    }
    if (stat == FAILED_REALLOC) {
        cerr << endl << "Failed to increase stack size";
        exit(FAILED_REALLOC);
    }
    if (stat == STACK_NOT_FOUND_SD) {
        cerr << endl <<"a null pointer is passed to Stack_Destroy";
        exit(STACK_NOT_FOUND_SD);
    }
    if (stat == STACK_NOT_FOUND_SP) {
        cerr << endl << "a null pointer is passed to Stack_Push";
        exit(STACK_NOT_FOUND_SP);
    }
    if (stat == REACH_MIN) {
        cerr << endl << "out of stack (stack is empty)";
        exit(REACH_MIN);
    }
    if (stat == FAILED_CREATE_STACK) {
        cerr << endl << "failed to set stack";
        exit(FAILED_CREATE_STACK);
    }

}