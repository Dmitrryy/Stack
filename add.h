#ifndef STACK_2_ADD_H
#define STACK_2_ADD_H

#include <cctype>
#include <cstddef>
#include <iostream>

template <typename X>
struct Stack {
    X* data;
    int size;
    int n_now;
};

template <typename T>
int Stack_Push (Stack <T> * st, T value);
template <typename T>
T Stack_Pop (Stack <T> * st);
template <typename Z>
struct Stack <Z>* Stack_Create (size_t nelem);
template <typename T>
int Stack_Destroy (Stack <T>* st);
template <typename T>
int my_realloc (Stack <T>* st);

#endif //STACK_2_ADD_H
