#include "Stack.h"
#include <cmath>

#define CREATE_STACK(T, name, size); \
 Stack <T>* name = (Stack <T>*) VirtualAlloc (NULL, size * sizeof(T) + sizeof(Stack<T>), MEM_COMMIT, PAGE_READONLY); \
 name->Create(size);

using namespace std;

/*template <typename T>
void Stack<T>::m_realloc() {
	unsigned long h = 0;
	VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
	if (h != PAGE_READONLY)
		OK(ERROR_CHANGE_PROTECT);

	m_nom_page++;
	Stack <T>* pt = (Stack <T>*)VirtualAlloc(this + 0x10000, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
	if (pt == NULL)
		OK(FAILED_REALLOC);

	m_size += (PAGE_SIZE - sizeof(Stack<T>)) / sizeof(T);

	OK(0);
}*/

template <typename T>
void Stack<T>::Create(int size) {
    if (size <= 0)
        OK(NEG_SIZE_STACK);
    OK(0);

    unsigned long h = 0;
    VirtualProtect(this, size * sizeof(T) + sizeof(Stack<T>), PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT_IN_CR);

    if (m_data != NULL)
        OK(STACK_IS_CREATED);

    m_nom_page = ceil((size * sizeof(T) + sizeof(Stack<T>)) / PAGE_SIZE) + 1;
    m_size = (PAGE_SIZE * m_nom_page - sizeof(Stack<T>)) / sizeof(T);

    m_data = (T*)((char*)this + sizeof(Stack<T>));

    OK(0);

#ifndef DISABLE_CHECK_PROTECT
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT_IN_CR);
#endif
}

template <typename T>
void Stack<T>::Destroy() {

#ifndef DISABLE_CHECK_PROTECT
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);
#endif

    VirtualFree(this, 0, MEM_RELEASE);
}

template <typename T>
void Stack<T>::Push(T value) {

#ifndef DISABLE_CHECK_PROTECT
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);
#endif

    OK(0);

    //if (m_n_now >= m_size)
    //  m_realloc();
    if (m_n_now == m_size)
        OK(REACH_MAX);

    m_data[m_n_now++] = value;
    OK(0);

#ifndef DISABLE_CHECK_PROTECT
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT);
#endif
}

template <typename T>
T Stack<T>::Pop() {

#ifndef DISABLE_CHECK_PROTECT
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);
#endif

    OK(0);

    if (m_n_now - 1 < 0)
        OK(REACH_MIN);

    T ret = m_data[--m_n_now];
    m_data[m_n_now] = 0;

    OK(0);

#ifndef DISABLE_CHECK_PROTECT
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT);
#endif

    return ret;
}


template <typename T>
void Stack<T>::OK(int stat) {

    if (stat == 0) {
        if (this == NULL) {
            cout << endl << "The pointer to Stack is zero (it may not have been created)." << endl
                 << "Try calling the \"Create\" function" << endl;
            exit(STACK_NOT_FOUND);
        }
    }
    else {
        if (stat == NEG_SIZE_STACK) {
            cout << endl << "In the stack creation function (CREATE_STACK(T, name, size);) pass a negative size" << endl
                 << "Cannot create a stack of negative size" << endl;
            exit(NEG_SIZE_STACK);
        }
        if (stat == STACK_IS_CREATED) {
            cout << endl << "Stack is created several times" << endl
                 << "Remove the old before creating a new it" << endl;
            Dump();
            exit(STACK_IS_CREATED);
        }
        /*if (stat == FAILED_REALLOC) {
            cout << endl << "failed to increase the size of the Data" << endl;
            exit(FAILED_REALLOC);
        }*/
        if (stat == REACH_MIN) {
            //SetConsoleTextAttribute ((HANDLE)GENERIC_WRITE, FOREGROUND_RED);
            cout << endl << "\"Pop\" function is used when Stack is empty" << endl;
            Dump();
            exit(REACH_MIN);
        }
        if (stat == ERROR_CHANGE_PROTECT) {
            cout << endl << "failed to change protection mode" << endl;
            Dump();
            exit(ERROR_CHANGE_PROTECT);
        }
        if (stat == ERROR_CHANGE_PROTECT_IN_CR) {
            cout << endl << "failed to change protection mode when creating stack" << endl;
            exit(ERROR_CHANGE_PROTECT_IN_CR);
        }
        if (stat == REACH_MAX) {
            cout << endl << "\"Push\" function is used when Stack is full" << endl
                 << "it is not possible to put an item in a full Stack" << endl;
            Dump();
            exit(REACH_MAX);
        }
    }
}

template <typename T>
void Stack<T>::Dump() {
    ofstream fout;
    fout.open("ferror.txt");

/*#ifndef DISABLE_CHECK_PROTECT
	unsigned long h = 0;
	VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
	if (h != PAGE_READONLY)
		OK(ERROR_CHANGE_PROTECT);
#endif*/

    fout << endl << "this = " << this << endl;
    fout << "data = " << m_data << endl;
    fout << "size = " << m_size << endl;
    fout << "type (sizeof) = " << sizeof(T) << endl;
    fout << "nom elements = " << m_n_now << endl;
    fout << "nom page = " << m_nom_page << endl << endl;

    fout << "content data: " << endl << endl;
    for (int i = 1; i < m_size + 1; i++)
        fout << "[" << i << "]  " << m_data[i - 1] << endl;
    fout.close();
}