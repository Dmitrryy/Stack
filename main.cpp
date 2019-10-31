#include "Stack.h"
#include "Stack.cpp"
using namespace std;

int main() {
    Stack <int> S;

    S.Stack_Create (1);

    S.Stack_Push (9);
    S.Stack_Push (12);

    cout << S.Stack_Pop() << endl;
    cout << S.Stack_Pop() << endl;
    //cout << Stack_Pop <int>(si) << endl;

    S.Stack_Destroy();

    return 0;
}