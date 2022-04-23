#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

struct IT {
    map<int, int> t[2][N << 2];

    void 
} it;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int k, x;
            cin >> k >> x;
            vector<int> ls(k);
            for (int &u : ls) cin >> u;
            it.update(1, 1, m, x, ls);
        } else {
            int d, x;
            cin >> d >> x;
        }
    }
    return 0;
}