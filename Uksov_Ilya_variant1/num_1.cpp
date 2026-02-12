#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите сначала число a, затем число b, для поиска их гипотенузы: ";
	int a, b;
	cin >> a >> b;

	cout << "Гипотенуза от чисел " << a << ' ' << b << " равняется " << sqrt((a * a) + (b * b));

	return 0;
}