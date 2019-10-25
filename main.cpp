#include "add.h"
using namespace std;

int main() {
    Stack <int>* si;

    si = Stack_Create <int>(1);

    Stack_Push <int>(si, 9);
    Stack_Push <int>(si, 12);

    cout << Stack_Pop <int>(si) << endl;
    cout << Stack_Pop <int>(si) << endl;
    cout << Stack_Pop <int>(si) << endl;

    Stack_Destroy(si);

    return 0;
}