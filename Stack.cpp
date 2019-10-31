
#include "Stack.h"

template <typename T>
void Stack<T>::m_realloc() {
    //if (st == 0)
      //  OK (STACK_NOT_FOUND_MR);

    T* tem = new T [m_size + (m_size + 2)]();
    //if (tem == NULL)
      //  OK (FAILED_REALLOC);
    memcpy (tem, m_data, m_size);
    delete (m_data);

    m_size += 2;
    m_data = tem;
}

template <typename T>
void Stack<T>::Stack_Create (size_t nelem) {
    //auto* st = new struct Stack <T>();
    //if (st == NULL)
      //  OK (FAILED_CREATE_STACK);

    m_data = new T [nelem]();
    m_size = nelem;

    //if (st->data == NULL)
      //  OK (FAILED_CREATE_STACK);
}

template <typename T>
void Stack<T>::Stack_Destroy () {
    //if (st == NULL)
      //  OK (STACK_NOT_FOUND_SD);

    delete [] m_data;
    delete this;
}

template <typename T>
void Stack<T>::Stack_Push (T value) {
    //if (st == NULL)
      //  OK (STACK_NOT_FOUND_SP);
    if (m_n_now >= m_size)
        m_realloc();

    m_data[m_n_now++] = value;
}

template <typename T>
T Stack<T>::Stack_Pop () {
    //if (st == NULL)
      //  OK (STACK_NOT_FOUND_SP);
    //if (st->n_now <= 0)
      //  OK (REACH_MIN);

    T ret = m_data[--m_n_now];
    m_data[m_n_now] = 0;

    return ret;
}