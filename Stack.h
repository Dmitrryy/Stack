
#ifndef STACK_2_STACK_H
#define STACK_2_STACK_H

#include "error.h"

#define CAN 0xAB010DED
#define CAN_DATA '%'

#include <cstddef>
#include <iostream>
#include <cctype>
#include <functional>
#include <ctime>

template <typename T>
class Stack {
private: unsigned long long m_can1 = CAN;
private: T* m_data = NULL;
private: int m_size = 0;
private: int m_n_now = 1;

private: unsigned long m_hash = 0;
private: T* m_hash_data = 0;
private: int m_stat = 0;

private: void m_realloc ();
private: void OK();
private: void Dump();
private: unsigned long counter_hash ();

public: void Create (int nelem);
public: void Destroy ();
public: void Push (T value);
public: T Pop ();

private: unsigned long long m_can2 = CAN;
};


#endif //STACK_2_STACK_H
