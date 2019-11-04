#include "Stack.h"
#include "Stack.cpp"

using namespace std;

int main() {
    Stack <int> S;

    S.Create();

    for (int i = 0; i < 4096; i++)
        S.Push(7);

    for (int i = 4096; i > 0; i--)
        cout << S.Pop() << endl;

    S.Push(10);

    S.Destroy();

    return 0;
}