#include "Stack.h"
#include "Stack.cpp"

using namespace std;

int main() {
    Stack <int> S;

    S.Create (3);

    S.Push (9);
    S.Push (12);
    S.Push (5);
    S.Push (432);
    S.Push(43);

    cout << S.Pop() << endl;
    cout << S.Pop() << endl;
    cout << S.Pop() << endl;
    cout << S.Pop() << endl;

    S.Push(10);

    S.Destroy();

    return 0;
}