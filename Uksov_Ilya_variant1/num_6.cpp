#include <iostream>
#include <cmath>


using namespace std;

struct Point {
	double x; 
	double y;
};

int main() {
	setlocale(LC_ALL, "Russian");
	
	int n;
	cout << "Введите количество точек: ";
	cin >> n;

	if (n <= 0) {
		cout << "Количество точек должно быть положительным!\n";
		return 1;
	}

	Point* points = new Point[n];

	cout << "Введите координаты точек (x y):\n";
	for (int i = 0; i < n; ++i) {
		cin >> points[i].x >> points[i].y;
	}

	int max_index = 0;
	double max_distance = 0;

	for (int i = 0; i < n; ++i) {
		double distance = sqrt(points[i].x * points[i].x + points[i].y * points[i].y);
		if (distance > max_distance) {
			max_distance = distance;
			max_index = i;
		}
	}

	cout << "Наиболее удалённая точка: (" << points[max_index].x << "; "
		<< points[max_index].y << ")";

	return 0;
}
