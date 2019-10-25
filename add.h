#ifndef STACK_2_ADD_H
#define STACK_2_ADD_H

#include <cctype>
#include <cstddef>
#include <iostream>

#include "error.h"

int OK (int stat);

template <typename X>
struct Stack {
    X* data;
    int size;
    int n_now;
};

template <typename T>
void my_realloc (struct Stack <T>* st) {
    if (st == 0)
        OK (STACK_NOT_FOUND_MR);
    T* tem = new T [st->size + (st->size + 2)]();
    if (tem == NULL)
        OK (FAILED_REALLOC);
    memcpy (tem, st->data, st->size);
    delete (st->data);
    st->size += 2;
    st->data = tem;
}

template <typename T>
struct Stack <T>* Stack_Create (size_t nelem) {
    auto* st = new struct Stack <T>();
    if (st == NULL)
        OK (FAILED_CREATE_STACK);

    st->data = new T [nelem]();
    st->size = nelem;

    if (st->data == NULL)
        OK (FAILED_CREATE_STACK);

    return st;
}

template <typename T>
void Stack_Destroy (Stack <T> * st) {
    if (st == NULL)
        OK (STACK_NOT_FOUND_SD);

    delete [] st->data;
    delete st;
}

template <typename T>
void Stack_Push (Stack <T> * st, T value) {
    if (st == NULL)
        OK (STACK_NOT_FOUND_SP);
    if (st->n_now >= st->size)
        my_realloc(st);

    st->data[st->n_now++] = value;
}

template <typename T>
T Stack_Pop (Stack <T> * st) {
    if (st == NULL)
        OK (STACK_NOT_FOUND_SP);
    if (st->n_now <= 0)
        OK (REACH_MIN);
    T ret = st->data[--st->n_now];
    st->data[st->n_now] = 0;

    return ret;
}



#endif //STACK_2_ADD_H
