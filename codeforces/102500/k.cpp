#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int s, d, t;
int n;
int l[N], r[N];
map<int, long long> dp;

long long get(int u) {
    if (u == 0) return 0;
    long long res = u;
    res = min(res, 1ll * (u / d) * t + u % d);
    res = min(res, 1ll * ((u - 1) / d + 1) * t);
    return res;
}

long long solve(int u) {
    if (u >= s) return 0;
    if (dp.count(u)) return dp[u];
    int id = 1;
    while (id <= n && r[id] <= u) id++;
    if (id == n + 1) return get(s - u);
    long long res = 1e18;
    if (l[id] > u) res = min(res, solve(l[id]) + get(l[id] - u));
    for (int i = id; i <= n; i++) {
        int dest = r[i] - d;
        if (dest > u && dest <= l[id]) res = min(res, solve(dest) + get(dest - u));
    }
    int dest = s - d;
    if (dest > u && dest <= l[id]) res = min(res, solve(dest) + get(dest - u));
    int now = u + d;
    for (int i = id; i <= n; i++) {
        if (l[i] <= now && now < r[i]) now = l[i];
    }
    if (now >= r[id]) res = min(res, solve(now) + t);
    dest = l[id] - (l[id] - u) % d;
    if (dest > u) res = min(res, solve(dest) + get(dest - u));
    return dp[u] = res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s >> d >> t;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    cout << solve(0) << endl;
    return 0;   
}