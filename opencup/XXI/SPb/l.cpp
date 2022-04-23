#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 998244353;
inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

struct NTT {
    int base = 1;
    int maxBase = 0;
    int root = 2;
    vector<int> w = {0, 1};
    vector<int> rev = {0, 1};
    NTT () {
        int u = MOD - 1;
        while (u % 2 == 0) {
            u >>= 1;
            maxBase++;
        }
        while (power(root, 1 << maxBase) != 1 || power(root, 1 << (maxBase - 1)) == 1) root++;
    }
    void ensure(int curBase) {
        assert(curBase <= maxBase);
        if (curBase <= base) return;
        rev.resize(1 << curBase);
        for (int i = 0; i < (1 << curBase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (curBase - 1));
        }
        w.resize(1 << curBase);
        for (; base < curBase; base++) {
            int wc = power(root, 1 << (maxBase - base - 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                w[i << 1] = w[i];
                w[i << 1 | 1] = mul(w[i], wc);
            }
        }
    }
    void fft(vector<int> &a) {
        int n = a.size();
        int curBase = 0;
        while ((1 << curBase) < n) curBase++;
        ensure(curBase);
        int shift = base - curBase;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < k; i++) {
                for (int j = i; j < n; j += k * 2) {
                    int foo = a[j];
                    int bar = mul(a[j + k], w[i + k]);
                    a[j] = add(foo, bar);
                    a[j + k] = sub(foo, bar);
                }
            }
        }
    }
    vector<int> mult(vector<int> a, vector<int> b) {
        int nResult = a.size() + b.size() - 1;
        int curBase = 0;
        while ((1 << curBase) < nResult) curBase++;
        ensure(curBase);
        int n = 1 << curBase;
        a.resize(n), b.resize(n);
        fft(a);
        fft(b);
        int invN = inv(n);
        for (int i = 0; i < n; i++) {
            a[i] = mul(mul(a[i], b[i]), invN);
        }
        reverse(a.begin() + 1, a.end());
        fft(a);
        a.resize(nResult);
        return a;
    }
} ntt;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, l, r;
    cin >> n >> l >> r;
    const int MAX_SIZE = 21;
    vector<int> res(1 << MAX_SIZE, 0);
    for (int it = 0; it < 1; it++) {
        vector<int> f(1 << 21);
        for (int i = 1; i <= n; i++) {
            int u;
            cin >> u;
            f[u] = rng() % (MOD - 1) + 1;
        }
        ntt.fft(f);
        for (int &u : f) {
            u = mul(sub(power(u, r + 1), power(u, l)) , inv(sub(u, 1)));
        }
        reverse(f.begin() + 1, f.end());
        ntt.fft(f);
        for (int i = 0; i < f.size(); i++) {
            res[i] |= f[i] != 0;
        }
    }
    cout << accumulate(res.begin(), res.end(), 0) << endl;
    return 0;
}