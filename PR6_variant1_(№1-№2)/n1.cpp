#include <iostream>
#include <string>


using namespace std;

class Message
{
private:
	string text;

public:
	///Создаем сообщение
	Message() {
		cout << "Введите текст вашего сообщения: " << endl;
		getline(cin, text);
		cout << endl << "Создано сообщение: " << text << endl;
	}
	///Удаляем сообщение
	~Message() {
		cout << "Удалено сообщение: " << text << endl;
	}

	void print() {
		cout << text << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");

	//Создаем стандартное сообщение и через динамическое выделение памяти
	Message first = Message();
	Message* second = new Message();

	first.print();
	second->print();
	delete(second);

	return 0;
}


