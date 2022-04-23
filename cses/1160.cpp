#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOG = 20;

int n, q;
int to[N];

int numComponent = 0;
int componentId[N];
int circleSize[N];

int posInCircle[N];

vector<int> revAdj[N];
int posIn[N], posOut[N], cntEuler = 0;
int depth[N];
int ancestor[LOG][N];

void dfs(int u, int p) {
    ancestor[0][u] = p;
    for (int i = 1; i < LOG; i++) ancestor[i][u] = ancestor[i - 1][ancestor[i - 1][u]];
    posIn[u] = ++cntEuler;

    for (int v : revAdj[u]) {
        if (posInCircle[v] != -1) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    posOut[u] = cntEuler;
}

int getAncestor(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) {
            u = ancestor[i][u];
        }
    }
    return u;
}

bool isAncestor(int u, int v) {
    return posIn[u] <= posIn[v] && posOut[v] <= posOut[u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> to[i];
        revAdj[to[i]].push_back(i);
    }

    fill(posInCircle + 1, posInCircle + n + 1, -1);

    // gen component
    for (int i = 1; i <= n; i++) {
        if (componentId[i]) continue;
        vector<int> ls;
        map<int, int> posInStack;
        int cur = i;
        while (!componentId[cur] && posInStack.find(cur) == posInStack.end()) {
            posInStack[cur] = ls.size();
            ls.push_back(cur);
            cur = to[cur];
        }
        if (!componentId[cur]) { // circle
            numComponent++;
            for (int u : ls) {
                componentId[u] = numComponent;
            }
            circleSize[numComponent] = ls.size() - posInStack[cur];
            for (int i = posInStack[cur], id = 0; i < ls.size(); i++, id++) {
                posInCircle[ls[i]] = id;
            }
        } else { // already considered cur
            for (int u : ls) {
                componentId[u] = componentId[cur];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (posInCircle[i] != -1) {
            dfs(i, 0);
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        if (componentId[a] != componentId[b]) {
            cout << -1 << '\n';
        } else {
            if (!isAncestor(b, a)) {
                if (posInCircle[b] == -1) {
                    cout << -1 << '\n';
                } else {
                    int res = depth[a];
                    a = getAncestor(a, depth[a]);
                    res += (posInCircle[b] - posInCircle[a] + circleSize[componentId[a]]) % circleSize[componentId[a]];
                    cout << res << '\n';
                }
            } else {
                cout << depth[a] - depth[b] << '\n';
            }
        }
    }
    return 0;
}