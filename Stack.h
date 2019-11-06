
#ifndef STACK_2_STACK_H
#define STACK_2_STACK_H

#include "error.h"

#define CAN 0xAB010DED

#define PAGE_SIZE 4096

#include <cstddef>
#include <iostream>
#include <cctype>
#include <functional>
#include <ctime>
#include <windows.h>

template <typename T>
class Stack {
private: T* m_data = NULL;
private: int m_size = 0;
private: int m_n_now = 0;
private: int m_nom_page = 0;

private: void m_realloc ();
private: void OK(int stat);
private: void Dump();

public: void Create ();
public: void Destroy ();
public: void Push (T value);
public: T Pop ();
};


#endif //STACK_2_STACK_H
