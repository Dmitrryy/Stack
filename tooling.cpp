#include "add.h"

template <typename T>
struct Stack <T>* Stack_Create (size_t nelem) {
    struct Stack <T>* st = new struct Stack <T>*;
    //if (st == NULL)
      //  return 1;
    st->data = new T [nelem];
    if (st->data == NULL)
        return 2;

    return st;
}

template <typename T>
int Stack_Destroy (Stack <T> * st) {
    if (st == NULL)
        return 3;

    delete st->data;
    delete st;
    return 0;
}

template <typename T>
int Stack_Push (Stack <T> * st, T value) {
    if (st == NULL)
        return 4;
    if (st->n_now >= st->size) {
        int state = my_realloc(st);
        if (state != 0)
            return state;
    }
    st->data[st->n_now++] = value;

    return 0;
}

template <typename T>
T Stack_Pop (Stack <T> * st) {
    if (st->n_now <= 0)
        return 5;
    T ret = st->data[st->n_now];
    st->data[st->n_now--] = 0;

    return ret;
}