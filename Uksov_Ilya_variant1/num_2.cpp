#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите сначала число a, потом число b, а потом число c, для поиска наибольшего из них: ";
	int a, b, c;
	cin >> a >> b >> c;

	cout << "Наибольшее из чисел " << a << ' ' << b << ' ' << c << " равняется " << max(max(a, b), c);

	return 0;
}