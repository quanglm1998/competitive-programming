#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOG = 20;

int n, m;
int a[N];
int maxVal[LOG][N];
int lg2[N];
int dp[N];

int rmq(int l, int r) {
    int lg = lg2[r - l + 1];
    return max(maxVal[lg][l], maxVal[lg][r - (1 << lg) + 1]);
}

bool check(pair<int, int> &u, pair<int, int> &v) {
    return u.first <= v.first && u.second <= v.second;
}

struct IT {
    int t[N << 2];

    void init(int node, int l, int r) {
        t[node] = N;
        if (l < r) {
            int m = l + r >> 1;
            init(node << 1, l, m);
            init(node << 1 | 1, m + 1, r);
        }
    }

    void update(int node, int l, int r, int x, int val) {
        if (x > r || x < l) return;
        if (l == r) {
            t[node] = min(t[node], val);
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x, val);
        update(node << 1 | 1, m + 1, r, x, val);
        t[node] = min(t[node << 1], t[node << 1 | 1]);
    }

    int get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return N;
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        int res = N;
        res = min(res, get(node << 1, l, m, x, y));
        res = min(res, get(node << 1 | 1, m + 1, r, x, y));
        return res;
    }
} it;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    lg2[1] = 0;
    for (int i = 2; i < N; i++) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            maxVal[0][i] = a[i];
        }
        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                maxVal[i][j] = max(maxVal[i - 1][j], maxVal[i - 1][j + (1 << i - 1)]);
            }
        }
        cin >> m;
        vector<pair<int, int>> heroes(m);
        for (auto &u : heroes) {
            cin >> u.second >> u.first;
        }
        sort(heroes.begin(), heroes.end());
        vector<pair<int, int>> now;
        for (auto u : heroes) {
            while (!now.empty() && check(now.back(), u)) now.pop_back();
            now.push_back(u);
        }
        heroes.swap(now);
        it.init(1, 1, n);
        dp[n + 1] = 0;
        for (int i = n; i >= 0; i--) {
            int low = i - 1, high = n + 1;
            while (high - low > 1) {
                int mid = low + high >> 1;
                int len = mid - i + 1;
                int id = lower_bound(heroes.begin(), heroes.end(), make_pair(len, -1)) - heroes.begin();
                if (id == heroes.size()) {
                    high = mid;
                    continue;
                }
                int val = rmq(i, mid);
                if (val <= heroes[id].second) low = mid;
                else high = mid;
            }
            it.update(1, 1, n, i, dp[i + 1]);
            if (low < i) dp[i] = N;
            else dp[i] = it.get(1, 1, n, i, low) + 1;
        }
        if (dp[1] >= N) cout << -1 << '\n';
        else cout << dp[1] << '\n';
    }
    return 0;
}