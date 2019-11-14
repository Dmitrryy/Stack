#include "Stack.cpp"

/**
 * @mainpage STACK
 * \brief Структура данных "Stack"
 * \author Дроздов Д.А.
 * \version 3.2
 * \date ноябрь 2019 года
 *
 * К функциям работы со Stack относятся:
 * void Create(int size);
 * void Destroy();
 * void Push(T value);
 * T Pop();
 *
 * Ниже приведен пример исспользования Stack. (калькулятор (польский))
 * Пример ввода: 8 9 + 1 7 - * =
 * Результат: -102
 */
int main() {

    char c = 0;
    int s = 0, a = 0, b = 0;

    CREATE_STACK(int, St, 40);

    cin >> c;

    St->Push(c - '0');

    for ( ; ; ) {
        cin >> c;

        if (c == '=')
            break;

        if (c >= '0' && c <= '9')
            St->Push(c - '0');

        if (c == '+') {
            a = St->Pop();
            b = St->Pop();
            s = a + b;
            St->Push(s);
        }

        if (c == '-') {
            b = St->Pop();
            a = St->Pop();
            s = a - b;
            St->Push(s);
        }

        if (c == '*') {
            a = St->Pop();
            b = St->Pop();
            s = a * b;
            St->Push(s);
        }
    }
    cout << s << endl;

    St->Destroy();
    return 0;
}