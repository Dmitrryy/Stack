#include "Stack.h"

#define CREATE_STACK(T, name) \
 Stack <T>* name = (Stack <T>*) VirtualAlloc (NULL, PAGE_SIZE, MEM_COMMIT, PAGE_READONLY); \
 name->Create();

using namespace std;

template <typename T>
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
}

template <typename T>
void Stack<T>::Create() {
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT_IN_CR);

    if (m_data != NULL)
        OK(STACK_IS_CREATED);

    //OK(0);

    m_size = (PAGE_SIZE - sizeof(Stack<T>)) / sizeof(T);
    m_nom_page = 1;

    m_data = (int*)((char*)this + sizeof(Stack<T>));

    OK(0);

    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT_IN_CR);
}

template <typename T>
void Stack<T>::Destroy() {
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);

    VirtualFree(this, 0, MEM_RELEASE);
}

template <typename T>
void Stack<T>::Push(T value) {
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);

    OK(0);

    if (m_n_now >= m_size)
        m_realloc();

    m_data[m_n_now++] = value;
    OK(0);

    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT);
}

template <typename T>
T Stack<T>::Pop() {
    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READWRITE, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);

    OK(0);

    if (m_n_now - 1 < 0)
        OK(REACH_MIN);

    T ret = m_data[--m_n_now];
    m_data[m_n_now] = 0;

    OK(0);

    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READWRITE)
        OK(ERROR_CHANGE_PROTECT);

    return ret;
}


template <typename T>
void Stack<T>::OK(int stat) {
    if (stat == 0) {
        if (m_size <= 0) {
            cout << "The \"Create\" function is transferred a negative argument" << endl;
            exit(NEGATIVE_SIZE);
        }
        if (this == NULL) {
            cout << "The pointer to Stack is zero (it may not have been created)." << endl
                 << "Try calling the \"Create\" function" << endl;
            exit(STACK_NOT_FOUND);
        }
        if (m_data == NULL) {
            cout << "The pointer to Data is zero (it may not have been created)." << endl
                 << "Try calling the \"Create\" function" << endl;
            exit(STACK_DATA_NOT_FOUND);
        }
    } else {
        if (stat == STACK_IS_CREATED) {
            cout << "Stack is created several times" << endl
                 << "Remove the old before creating a new it" << endl;
            exit(STACK_IS_CREATED);
        }
        if (stat == FAILED_REALLOC) {
            cout << "failed to increase the size of the Data" << endl;
            exit(FAILED_REALLOC);
        }
        if (stat == REACH_MIN) {
            cout << endl << "\"Pop\" function is used when Stack is empty" << endl;
            exit(REACH_MIN);
        }
    }
}

template <typename T>
void Stack<T>::Dump() {
    cout << "this = " << this << endl;
    cout << "data = " << m_data << endl;
    cout << "size = " << m_size << endl;
    cout << "nom elements = " << m_n_now << endl;

    unsigned long h = 0;
    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);

    cout << "[0]  " << m_data[0] << "  (CAN)" << endl;
    for (int i = 1; i < m_size + 1; i++)
        cout << "[" << i << "]  " << m_data[i] << endl;
    cout << "[" << m_size + 1 << "]  " << m_data[m_size + 1] << "  (CAN)" << endl;

    OK(0);

    VirtualProtect(this, PAGE_SIZE * m_nom_page, PAGE_READONLY, &h);
    if (h != PAGE_READONLY)
        OK(ERROR_CHANGE_PROTECT);
}