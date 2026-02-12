#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Введите размер массива: ";
	cin >> n;

	if (n <= 0) {
		cout << "Количество элементов должно быть положительным!";
		return 1;
	}

	int* arr = new int[n];

	cout << "Введите элементы массива (целые числа):\n";
	for (int i = 0; i < n; ++i) {
		cout << "Элемент " << i + 1 << ": ";
		cin >> arr[i];
	}

	bool found_chet = false;

	for (int i = 0; i < n; i++) {
		if (arr[i] % 2 == 0) {
			cout << arr[i] << " ";
			found_chet = true;
		}
	}

	if (!found_chet) {
		cout << "Нет чётных элементов!";
	}

	return 0;
}