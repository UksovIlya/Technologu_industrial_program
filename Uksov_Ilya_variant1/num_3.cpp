#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите сначала число a, потом число b, для поиска чеиных чисел между ними (до числа b включительно): ";
	int a, b;
	cin >> a >> b;

	if (a >= b) {
		cout << "Число должно a, быть больше числа b!";
		return 1;
	}

	cout << "Четные числа между числами " << a << ' ' << b << ':';
	for (int i = a; i <= b; i++) {
		if (i % 2 == 0) {
			cout << ", " << i;
		}
	}

	return 0;
}