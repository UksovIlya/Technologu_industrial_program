#include <iostream>
using namespace std;

int NOD(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

class Fraction {
    int a, b;

    void normalization() {
        if (b == 0) {
            a = 0;
            b = 1;
            return;
        }

        if (a >= b) {
            a = a % b;
        }

        if (a == 0) {
            b = 1;
            return;
        }

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

    void print() {
        cout << a << "/" << b << endl;
    }

    int getA() { 
        return a; 
    }
    int getB() { 
        return b; 
    }

    Fraction operator+(Fraction& f) {
        int n1 = a * f.b + f.a * b;
        int n2 = b * f.b;
        return Fraction(n1, n2);
    }

    Fraction operator*(Fraction& f) {
        int n1 = a * f.a;
        int n2 = b * f.b;
        return Fraction(n1, n2);
    }

    Fraction operator/(Fraction& f) {
        int n1 = a * f.b;
        int n2 = b * f.a;
        return Fraction(n1, n2);
    }
};

#include "main3_2.cpp"