#include "Stack.h"

using namespace std;

template <typename T>
void Stack<T>::m_realloc() {
    OK();

    T* tem = new T [m_size + 4]();
    if (&tem == NULL)
        m_stat == FAILED_REALLOC;
    OK ();

    memcpy (tem, m_data, sizeof(T) * (m_size + 2));
    delete (m_data);

    m_size += 2;
    m_data = tem;
    m_data[m_size + 1] = (T)CAN_DATA;

    m_stat = CHANGE_HASH;
    OK();
}

template <typename T>
void Stack<T>::Create (int nelem) {
    if (nelem <= 0 || m_data != NULL) {
        m_stat = STACK_IS_CREATED;
        OK();
    }
    m_size = nelem;

    m_data = new T [nelem + 2]();

    m_data[0] = (T)CAN_DATA;
    m_data[nelem + 1] = (T)CAN_DATA;

    m_hash_data = m_data;
    m_stat = CHANGE_HASH;
    OK();
}

template <typename T>
void Stack<T>::Destroy () {
    OK ();

    delete m_data;
    //delete this;
    m_data = NULL;
}

template <typename T>
void Stack<T>::Push (T value) {
    OK ();

    if (m_n_now > m_size)
        m_realloc();

    m_data[m_n_now++] = value;

    m_stat = CHANGE_HASH;
    OK();
}

template <typename T>
T Stack<T>::Pop () {
    m_n_now--;
    m_stat = CHANGE_HASH;
    OK();

    T ret = m_data[m_n_now];
    m_data[m_n_now] = 0;

    m_stat = CHANGE_HASH;
    OK();

    return ret;
}


template <typename T>
void Stack<T>::OK () {
    if (m_data == NULL) {
        cout << "The pointer to Data is zero (it may not have been created)." << endl
             << "Try calling the \"Create\" function" << endl;
        exit(STACK_DATA_NOT_FOUND);
    }
    if (m_size <= 0) {
        cout << "The \"Create\" function is transferred a negative argument" << endl;
        exit(NEGATIVE_SIZE);
    }
    if (m_stat == STACK_IS_CREATED) {
        cout << "Stack is created several times" << endl
             << "Remove the old before creating a new it" << endl;
        exit(STACK_IS_CREATED);
    }
    if (m_stat == FAILED_REALLOC) {
        cout << "failed to increase the size of the Data" << endl;
        exit(FAILED_REALLOC);
    }


    if (this == NULL) {
        cout << "The pointer to Stack is zero (it may not have been created)." << endl
             << "Try calling the \"Create\" function" << endl;
        exit(STACK_NOT_FOUND);
    }

    if (m_n_now <= 0) {
        cout << endl << "\"Pop\" function is used when Stack is empty" << endl;
        exit(REACH_MIN);
    }
    if (m_stat == CHANGE_HASH) {
        m_hash = counter_hash();
        m_stat = 0;
    }
    if (m_hash != counter_hash() && m_data != m_hash_data) {
        cout << "Changing the hash" << endl << "Stack is corrupted" << endl;
        exit(HASH_MISMATCH);
    }
    if (m_can1 != CAN || m_can2 != CAN) {
        cout << "Corrupted Stack (the value of Canaries changed)" << endl;
        exit(CAN_CHANGE);
    }
    if (m_data[0] != (T)CAN_DATA || m_data[m_size + 1] != (T)CAN_DATA) {
        cout << "Corrupted Stack (Data) (the value of Canaries changed)" << endl;
        exit(CAN_CHANGE_DATA);
    }
}

template <typename T>
unsigned long Stack<T>::counter_hash() {

    srand (time(NULL));
    static int r = rand();

    unsigned long new_hash = (m_size *385 - m_n_now * 67) % r;

    return new_hash;
}

template <typename T>
void Stack<T>::Dump() {
    cout << "can1 = " << m_can1 << endl;
    cout << "this = " << this << endl;
    cout << "size = " << m_size << endl;
    cout << "nom elements = " << m_n_now << endl;
    cout << "hash = " << m_hash << endl;
    cout << "hash Data = " << m_hash_data << endl;
    cout << "can2 = " << m_can2 << endl;

    cout << "[0]  " << m_data[0] << "  (CAN)" << endl;
    for (int i = 1; i < m_size + 1; i++)
        cout << "[" << i << "]  " << m_data[i] << endl;
    cout << "[" << m_size + 1 << "]  " << m_data[m_size + 1] << "  (CAN)" << endl;
}