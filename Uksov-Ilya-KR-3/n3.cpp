#include <iostream>
using namespace std;

int NOD(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

class Fraction {
    int a, b;

    void normalization() {
        if (b == 0) { a = 0; b = 1; return; }
        if (a >= b) a %= b;
        if (a == 0) { b = 1; return; }

        int g = NOD(a, b);
        a /= g;
        b /= g;
    }

public:
    Fraction() {
        a = 0;
        b = 1;
    }

    Fraction(int a, int b) {
        this->a = a;
        this->b = b;
        normalization();
    }

    Fraction operator+( Fraction& f) {
        return Fraction(a * f.b + f.a * b, b * f.b);
    }

    void print() {
        cout << a << "/" << b << endl;
    }
};

template <typename T>
T superSum(T a, T b) {
    return a + b;
}

template <typename T, size_t N>
T superSum(T (&arr)[N]) {
    T sum = T();
    for (size_t i = 0; i < N; i++) {
        sum = sum + arr[i];
    }
    return sum;
}

#include "main3_3.cpp"