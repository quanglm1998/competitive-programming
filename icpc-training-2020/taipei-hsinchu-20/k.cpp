#include <bits/stdc++.h>

using namespace std;

struct Solver {
    int BASE;
    vector<vector<uint64_t>> ff;

    Solver(int BASE) : BASE(BASE) {
        ff.assign(BASE + 1, vector<uint64_t>(BASE + 1, -1));
    }

    uint64_t f(int l, int num) {
        if (num == 0) return 1;
        if (ff[l][num] != -1) return ff[l][num];
        uint64_t &res = ff[l][num];
        if (l == 0) res = f(l + 1, num - 1) * (BASE - 1);
        else res = f(l + 1, num - 1) * (BASE - l);
        return res;
    }

    uint64_t getSmaller(uint64_t x) {
        int64_t low = 0, high = 1e18;
        while (high - low > 1) {
            int64_t mid = (low + high) >> 1;
            uint64_t num = getNumber(mid);
            if (num == -1 || num > x) high = mid;
            else low = mid;
        }
        return low;
    }

    uint64_t getNumber(uint64_t id) {
        if (id == 1) return 0;
        id--;
        int len = -1;
        for (int i = 1; i <= BASE; i++) {
            if (f(0, i) < id) {
                id -= f(0, i);
            } else {
                len = i;
                break;
            }
        }
        if (len == -1) return -1;
        uint64_t res = 0;
        vector<bool> used(BASE, 0);
        for (int i = 0; i < len; i++) {
            int foo = -1;
            for (int x = (i == 0); x < BASE; x++) {
                if (used[x]) continue;
                if (f(i + 1, len - i - 1) < id) id -= f(i + 1, len - i - 1);
                else {
                    foo = x;
                    break;
                }
            }
            assert(foo != -1);
            res = res * BASE + foo;
            used[foo] = 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;

    Solver solver10(10);
    Solver solver16(16);

    while (n--) {
        char type;
        Solver *solver;
        int op;

        cin >> type;
        if (type == 'h') {
            cin >> hex;
            cout << hex;
            solver = &solver16;
        } else {
            cin >> dec;
            cout << dec;
            solver = &solver10;
        }
        cin >> op;
        if (op == 0) {
            uint64_t l, r;
            cin >> l >> r;
            uint64_t res = solver->getSmaller(r);
            if (l > 0) res -= solver->getSmaller(l - 1);
            cout << res << '\n';
        } else {
            uint64_t id;
            cin >> id;
            uint64_t foo = solver->getNumber(id);
            if (foo == -1) {
                cout << "-\n";
            } else {
                cout << foo << '\n';
            }
        }
    }
    return 0;
}