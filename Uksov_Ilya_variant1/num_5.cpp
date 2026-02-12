#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Введите строку в которой все символы поменяют свой регистр: ";
	string str;
	getline(cin, str);

	for (int i = 0; i < size(str); ++i) {
		if (isupper(str[i])) {
			str[i] = tolower(str[i]);
		}
		else {
			str[i] = toupper(str[i]);
		}
	}

	cout << str;

	return 0;
}