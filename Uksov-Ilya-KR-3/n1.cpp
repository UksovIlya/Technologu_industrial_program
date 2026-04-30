#include <iostream>
#include <vector>
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

    bool operator==(Fraction& f)  {
        return a == f.a && b == f.b;
    }
};

class SetOfFractions {
    vector<Fraction> data;

public:
    bool isEmpty() {
        return data.empty();
    }

    void append(Fraction f) {
        for (Fraction &x : data) {
            if (x == f) return;
        }
        data.push_back(f);
    }

    void exclude(Fraction f) {
        for (Fraction it = data.begin(); it != data.end(); ++it) {
            if (*it == f) {
                data.erase(it);
                return;
            }
        }
    }

    Fraction sum() {
        if (data.empty()) return Fraction();

        int n1 = 0;
        int n2 = 1;

        for (auto &f : data) {
            n1 = n1 * f.getB() + f.getA() * n2;
            n2 = n2 * f.getB();

            int g = NOD(n1, n2);
            n1 /= g;
            n2 /= g;
        }

        return Fraction(n1, n2);
    }
};

#include "main3_1.cpp"