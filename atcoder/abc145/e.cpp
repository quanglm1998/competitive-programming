#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int MOD = 1000000007;
const int INF = 2e9;

inline int add(int u, int v) {return (u += v) >= MOD ? u - MOD : u;}
inline int sub(int u, int v) {return (u -= v) < 0 ? u + MOD : u;}
inline int mul(int u, int v) {return (long long)u * v % MOD;}
inline int power(int u, int v) {int res = 1;for (; v; v >>= 1, u = mul(u, u)) if (v & 1) res = mul(res, u); return res;}
inline int inv(int u) {return power(u, MOD - 2);}
inline void addTo(int &u, int v) {u = add(u, v);}
inline void subTo(int &u, int v) {u = sub(u, v);}
inline void mulTo(int &u, int v) {u = mul(u, v);}

int n;
int a[N];
int id[N];
int res = 0;
int dp[N][N];

int C(int n, int k) {
    int res = 1;
    for (int i = 0; i < k; i++) {
        mulTo(res, sub(n, i));
        mulTo(res, inv(i + 1));
    }
    return res;
}

int get(vector<int> now) {
    vector<int> ls;
    for (int i = 1; i <= n; i++) {
        int u = id[i];
        int it = lower_bound(ls.begin(), ls.end(), u) - ls.begin();
        if (it == ls.size()) ls.push_back(u);
        else ls[it] = u;
    }

    vector<int> val = now;
    sort(val.begin(), val.end());
    val.resize(unique(val.begin(), val.end()) - val.begin());
    for (int i = 0; i <= now.size(); i++) {
        for (int j = 0; j <= val.size(); j++) {
            dp[i][j] = (i == 0);
        }
    }   
    for (int i = 1; i <= now.size(); i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= val.size(); j++) {
            dp[i][j] = dp[i][j - 1];
            int sz = val[j - 1] - (j == 1 ? 0 : val[j - 2]);
            for (int k = i; k >= 1; k--) {
                if (now[k - 1] < val[j - 1]) break;
                addTo(dp[i][j], mul(C(sz, i - k + 1), dp[k - 1][j - 1]));
            }
        }
    }
    return mul((int)ls.size(), dp[now.size()][val.size()]);
}

void solve(int u, vector<int> now) {
    vector<int> ls;
    for (int i = 1; i <= n; i++) {
        if (!id[i]) {
            ls.push_back(i);
        }
    }
    if (ls.empty()) {
        addTo(res, get(now));
        return;
    }
    for (int mask = 1; mask < 1 << ls.size(); mask++) {
        int cur = INF;
        for (int i = 0; i < ls.size(); i++) {
            if (mask >> i & 1) {
                id[ls[i]] = u;
                cur = min(cur, a[ls[i]]);
            }
        }

        now.push_back(cur);
        solve(u + 1, now);
        now.pop_back();

        for (int i = 0; i < ls.size(); i++) {
            if (mask >> i & 1) {
                id[ls[i]] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> foo;
    solve(1, foo);
    for (int i = 1; i <= n; i++) {
        mulTo(res, inv(a[i]));
    }
    cout << res << endl;
    return 0;
}