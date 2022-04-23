#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int a[N], b[N];
int orderA[N], orderB[N];
vector<int> deadLs;
int nxt[N];

int sumL[N], sumR[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    iota(orderA + 1, orderA + n + 1, 1);
    iota(orderB + 1, orderB + m + 1, 1);
    sort(orderA + 1, orderA + n + 1, [&](int u, int v) {
        return a[u] > a[v];
    });
    sort(orderB + 1, orderB + m + 1, [&](int u, int v) {
        return b[u] > b[v];
    });
    for (int i = 1; i <= n; i++) {
        if (a[i] + b[orderB[1]] < 0) deadLs.push_back(i);
    }

    int cur = 0;
    int minB = 0;
    for (int i = 1; i <= n; i++) nxt[i] = i - 1;
    function<int(int)> getNxt = [&](int u) {
        if (!u || u > n || a[u] + b[minB] >= 0) return u;
        return nxt[u] = getNxt(nxt[u]);
    };
    // left
    for (int i = 1; i <= n; i++) {
        int u = orderA[i];
        while (cur + 1 <= m && b[cur + 1] + a[u] < 0) {
            cur++;
            if (!minB || b[minB] > b[cur]) minB = cur;
        }
        if (cur) {
            sumL[getNxt(u) + 1]++;
            sumL[u + 1]--;
        }
    }
    // right
    cur = m + 1;
    minB = m + 1;
    for (int i = 1; i <= n; i++) nxt[i] = i + 1;
    for (int i = 1; i <= n; i++) {
        int u = orderA[i];
        while (cur - 1 >= 1 && b[cur - 1] + a[u] < 0) {
            cur--;
            if (minB > m || b[minB] > b[cur]) minB = cur;
        }
        if (cur <= m) {
            sumR[u]++;
            sumR[getNxt(u)]--;
        }
    }

    for (int i = 1; i <= n; i++) {
        sumL[i] += sumL[i - 1];
        sumR[i] += sumR[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        sumL[i] = sumL[i - 1] + (sumL[i] == 0);
        sumR[i] = sumR[i - 1] + (sumR[i] == 0);
    }

    minB = orderB[m];
    vector<pair<int, int>> rangeLs;
    for (int i = 1; i <= n; i++) {
        if (a[i] + b[minB] >= 0) continue;
        if (!rangeLs.empty() && rangeLs.back().second + 1 == i) rangeLs.back().second = i;
        else rangeLs.push_back({i, i});
    }

    int curDead = 0;
    int curRange = 0;
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        if (sumL[i] == sumL[i - 1]) continue;
        while (curDead < deadLs.size() && deadLs[curDead] < i) curDead++;
        while (curRange < rangeLs.size() && rangeLs[curRange].second < i) curRange++;
        
        int l = i, r = n;
        if (curDead < deadLs.size()) r = min(r, deadLs[curDead] - 1);
        if (curRange < rangeLs.size() && rangeLs[curRange].first <= i) l = max(l, rangeLs[curRange].second + 1);
        
        if (l <= r) res += sumR[r] - sumR[l - 1];
    }
    cout << res << '\n';
    return 0;
}