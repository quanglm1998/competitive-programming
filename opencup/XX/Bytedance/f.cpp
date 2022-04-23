#include <bits/stdc++.h>

using namespace std;

struct DynamicBitSet {
    int n;
    vector<uint32_t> a;
    
    DynamicBitSet(int sz) {
        n = (sz - 1) / 32 + 1;
        a.assign(n, 0);
    }

    DynamicBitSet operator|(const DynamicBitSet &o) const {
        DynamicBitSet res(n << 5);
        for (int i = 0; i < n; i++) {
            res.a[i] = a[i] | o.a[i];
        }
        return res;
    }

    DynamicBitSet operator<<(int k) const {
        int num = k / 32;
        DynamicBitSet res1(n << 5);
        for (int i = num; i < n; i++) {
            res1.a[i] = a[i - num];
        }
        k %= 32;
        if (k == 0) return res1;

        DynamicBitSet res(n << 5);
        uint32_t last = 0;
        for (int i = 0; i < n; i++) {
            res.a[i] = (last >> 32 - k) | (res1.a[i] << k);
            last = res1.a[i]; 
        }
        return res;
    }   

    int findPrev(int u) const {
        int pos = u / 32;
        int off = u % 32;
        if (a[pos] != 0) {
            for (int i = off; i >= 0; i--) {
                if (a[pos] >> i & 1) {
                    return pos << 5 | i;
                }
            }
        }
        pos--;
        while (a[pos] == 0) pos--;
        for (int i = 31; i >= 0; i--) if (a[pos] >> i & 1) return pos << 5 | i;
        return -1;
    }

    void set(int u) {
        int pos = u / 32;
        int off = u % 32;
        a[pos] |= (1 << off);
    }

    void debug() {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 31; j >= 0; j--) {
                cout << (a[i] >> j & 1);
            }
            cout << ' ';
        }
        cout << endl;
    }
};

int n, c;
int sum;
int a[20010];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    tc = 1;
    while (tc--) {
        // cin >> n >> c;
        sum = 0;
        for (int i = 1; i <= n; i++) {
            // cin >> a[i];
            a[i] = 20000;
            sum += a[i];
        }
        DynamicBitSet s(sum + 1);
        s.set(0);
        for (int i = 1; i <= n; i++) {
            s = (s << a[i]) | s;
        }
        c = min(c, sum);
        cout << s.findPrev(c) << '\n';
    }
    return 0;
}