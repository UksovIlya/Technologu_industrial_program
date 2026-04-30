#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int NOD(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

template <typename T>
class SuperFraction {
    int a, b;

    void normalize() {
        if (b == 0) { a = 0; b = 1; return; }

        if (a >= b) a %= b;

        if (a == 0) { b = 1; return; }

        int g = NOD(a, b);
        a /= g;
        b /= g;
    }

public:
    SuperFraction() : a(0), b(1) {}

    SuperFraction(T a, T b) {
        this->a = (int)floor(a);
        this->b = (int)floor(b);
        normalize();
    }

    void print() const {
        cout << a << "/" << b << endl;
    }

    bool operator==(const SuperFraction& other) const {
        return a == other.a && b == other.b;
    }

    SuperFraction operator+(const SuperFraction& other) const {
        return SuperFraction(
            a * other.b + other.a * b,
            b * other.b
        );
    }
};

template <typename T>
class SuperExtraMegaWowOfFractions {
    vector<SuperFraction<T>> data;

public:
    bool isEmpty() {
        return data.empty();
    }

    void append(SuperFraction<T> f) {
        for (auto &x : data) {
            if (x == f) return;
        }
        data.push_back(f);
    }

    void exclude(SuperFraction<T> f) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (*it == f) {
                data.erase(it);
                return;
            }
        }
    }

    SuperFraction<T> sum() {
        SuperFraction<T> res;

        for (auto &x : data) {
            res = res + x;
        }

        return res;
    }
};

#include "main3_4.cpp"