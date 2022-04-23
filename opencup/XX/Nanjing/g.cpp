#include <bits/stdc++.h>

using namespace std;

const int N = 600010;
const int CHAR = 26;

struct AC {
    int cnt;
    int nxt[CHAR][N];
    int suf[N];

    AC() {
        cnt = 1;
        memset(nxt, 0, sizeof nxt);
        memset(suf, 0, sizeof suf);
    }

    int add(const string &s) {
        int cur = 1;
        for (char u : s) {
            if (!nxt[u - 'a'][cur]) nxt[u - 'a'][cur] = ++cnt;
            cur = nxt[u - 'a'][cur];
        }
        return cur;
    }

    vector<int> adj[N];

    void build() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < CHAR; i++) {
                int v = u == 1 ? u : nxt[i][suf[u]];
                if (!nxt[i][u]) nxt[i][u] = v;
                else {
                    suf[nxt[i][u]] = v;
                }
            }
        }
    }   
} ac;

int n, m;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int a = 0, b = 1;
    (a == 1 ? a : b) = 1;
    cout << a << ' ' << b << endl;
    return 0;
}