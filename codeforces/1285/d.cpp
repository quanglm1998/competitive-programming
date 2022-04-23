#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 30;

int n;

struct Trie {
    int nxt[2][N * LOG + 10];
    int cnt;
    Trie() {
        cnt = 1;
    }
    void add(int u) {
        int cur = 1;
        for (int i = 29; i >= 0; i--) {
            int now = (u >> i) & 1;
            if (!nxt[now][cur]) nxt[now][cur] = ++cnt;
            cur = nxt[now][cur];
        }
    }

    int go(int u, int lv) {
        if (nxt[0][u] && nxt[1][u]) {
            return (1 << lv) + min(go(nxt[0][u], lv - 1), go(nxt[1][u], lv - 1));
        } else if (nxt[0][u]) {
            return go(nxt[0][u], lv - 1);
        } else if (nxt[1][u]) return go(nxt[1][u], lv - 1);
        return 0;
    }

    int calc() {
        return go(1, 29);
    }
} t;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        t.add(u);
    }
    cout << t.calc() << endl;
    return 0;
}