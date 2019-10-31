
#ifndef STACK_2_STACK_H
#define STACK_2_STACK_H

#include <cstddef>
#include <iostream>
#include <cctype>

template <typename T>
class Stack {
private: T* m_data;
private: int m_size;
private: int m_n_now;

private: void m_realloc ();

public: void Stack_Create (size_t nelem);
public: void Stack_Destroy ();
public: void Stack_Push (T value);
public: T Stack_Pop ();
};


#endif //STACK_2_STACK_H
