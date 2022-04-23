#include <bits/stdc++.h>

using namespace std;

struct Fraction {
    long long a, b;
    Fraction(long long a = 0, long long b = 0) : a(a), b(b) {}
    void normalize() {
        if (a == 0) {
            a = 0;
            b = 1;
            return;
        }
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
        long long g = __gcd(abs(a), abs(b));
        a /= g;
        b /= g;
    }
    Fraction operator + (const Fraction &u) const {
        Fraction res;
        res.a = a * u.b + b * u.a;
        res.b = b * u.b;
        res.normalize();
        return res;
    }
    Fraction operator - (const Fraction &u) const {
        Fraction res;
        res.a = a * u.b - b * u.a;
        res.b = b * u.b;
        res.normalize();
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string t;
    cin >> t;
    t = "+" + t;
    stringstream s(t);
    Fraction res(0, 1);
    char op;
    while (s >> op) {
        long long a;
        s >> a;
        char foo;
        s >> foo;
        long long b;
        s >> b;
        if (op == '+') res = (res + Fraction(a, b));
        else res = (res - Fraction(a, b));
    }
    cout << res.a << '/' << res.b << endl;
    return 0;
}