#include <iostream>
using namespace std;

class Counter {
private:
    int id;
    static int totalCounters;

public:
    ///Создаем счетчик
    Counter() {
        totalCounters++;
        id = totalCounters;
        cout << "Счётчик #" << id << " создан" << endl;
    }
    ///Удаляем счетчик
    ~Counter() {
        totalCounters--;
        cout << "Счётчик #" << id << " уничтожен" << endl;
    }

    static int getTotalCounters() {
        return totalCounters;
    }
};

///Создаем глобальную переменную
int Counter::totalCounters = 0;

int main() {
    setlocale(LC_ALL, "Rus");

    int N;
    cout << "Сколько счётчиков создать? ";
    cin >> N;

    if (N <= 0) {
        cout << "Количество счётчиков должно быть положительным числом!" << endl;
        return 1;
    }

    //создаем динамический массив с счетчиками
    Counter* counters = new Counter[N];
    cout << "Текущее количество счётчиков: " << Counter::getTotalCounters() << endl;
    delete[] counters;
    cout << "После удаления массива количество счётчиков: " << Counter::getTotalCounters() << endl;

    return 0;
}
