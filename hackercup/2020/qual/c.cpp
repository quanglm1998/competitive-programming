#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n;
pair<long long, long long> a[N];
long long dp[N * 3];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    vector<long long> ls;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        ls.push_back(a[i].first);
        ls.push_back(a[i].first - a[i].second);
        ls.push_back(a[i].first + a[i].second);
    }
    long long res = 0;
    sort(ls.begin(), ls.end());
    ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
    sort(a + 1, a + n + 1);

    auto getPos = [&](long long u) {
        return lower_bound(ls.begin(), ls.end(), u) - ls.begin();
    };

    fill(dp, dp + ls.size() + 1, 0);

    for (int i = 1; i <= n; i++) {
        int pos = getPos(a[i].first);
        int lPos = getPos(a[i].first - a[i].second);
        int rPos = getPos(a[i].first + a[i].second);
        long long lVal = dp[lPos] + a[i].second;
        long long rVal = dp[pos] + a[i].second;
        dp[pos] = max(dp[pos], lVal);
        dp[rPos] = max(dp[rPos], rVal);
    }
    cout << *max_element(dp, dp + ls.size() + 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}