#include <bits/stdc++.h>

using namespace std;

template<int MOD>
struct Modular {
    int val;

    Modular(long long u = 0) {
        val = ((u % MOD) + MOD) % MOD;
    }

    bool operator==(const Modular &o) const {
        return val == o.val;
    }

    bool operator!() const {
        return *this == 0;
    }

    Modular operator+(const Modular &o) const {
        int res = val + o.val;
        if (res >= MOD) res -= MOD;
        return {res};
    }

    Modular operator-(const Modular &o) const {
        int res = val - o.val;
        if (res < 0) res += MOD;
        return {res};
    }

    Modular operator*(const Modular &o) const {
        return {1ll * val * o.val % MOD};
    }

    Modular& operator+=(const Modular &o) {
        val += o.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }

    Modular& operator-=(const Modular &o) {
        val -= o.val;
        if (val < 0) val += MOD;
        return *this;
    }

    Modular& operator*=(const Modular &o) {
        val = 1ll * val * o.val % MOD;
        return *this;
    }

    Modular power(int v) const {
        Modular u = *this;
        Modular res = 1;
        while (v) {
            if (v & 1) res *= u;
            u *= u;
            v >>= 1;
        }
        return res;
    }

    Modular inv() const {
        return {this->power(MOD - 2)};
    }
};
template <int MOD>
ostream& operator<<(ostream& os, const Modular<MOD>& m) {
    return os << m.val;
}
constexpr int MOD = 998244353;
using Mint = Modular<MOD>;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    return 0;
}