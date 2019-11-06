#include "Stack.cpp"

using namespace std;

int main() {
    CREATE_STACK(int, S);

    S->Push(10);

    cout << S->Pop() << endl;

    S->Destroy();

    return 0;
}