#include "Stack.cpp"

int main() {
    CREATE_STACK(int, S, 10);

    CREATE_STACK(char, C, 4);

    CREATE_STACK(double, F, 4);

    CREATE_STACK(unsigned long long, LLD, 4);

    CREATE_STACK(char*, CP, 4);

    for (int i = 0; i < 1018; i++)
        S->Push(10);

    C->Push('v');

    F->Push(981.2138912);

    LLD->Push(8712369127821098301);

    cout << S->Pop() << endl;
    cout << C->Pop() << endl;
    cout << F->Pop() << endl;
    cout << LLD->Pop() << endl;

    S->Destroy();
    C->Destroy();
    F->Destroy();
    LLD->Destroy();

    return 0;
}