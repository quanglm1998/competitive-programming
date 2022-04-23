#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n;
pair<pair<int, int>, int> a[N];
vector<int> adj[N];
multiset<long long, greater<long long>> s[N];
bool used[N];

void join(multiset<long long, greater<long long>> &u, multiset<long long, greater<long long>> &v) {
    if (u.size() < v.size()) u.swap(v);
    vector<long long> now;
    int sz = v.size();
    for (int i = 0; i < sz; i++) {
        now.push_back(*u.begin() + *v.begin());
        u.erase(u.begin());
        v.erase(v.begin());
    }
    for (long long val : now) u.insert(val);
}

void dfs(int u) {
    used[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
        join(s[u], s[v]);
    }
    s[u].insert(a[u].second);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first.first >> a[i].first.second >> a[i].second;
        a[i].first.second--;
    }
    sort(a + 1, a + n + 1, [&](pair<pair<int, int>, int> u, pair<pair<int, int>, int> v) {
        if (u.first.first != v.first.first) return u.first.first < v.first.first;
        return u.first.second > v.first.second;
    });
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()].first.second < a[i].first.first) st.pop_back();
        if (!st.empty()) {
            adj[st.back()].push_back(i);
        }
        st.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i);
            join(s[0], s[i]);
        }
    }
    long long cur = 0;
    for (int i = 1; i <= n; i++) {
        if (!s[0].empty()) {
            cur += *s[0].begin();
            s[0].erase(s[0].begin());
        }
        cout << cur << ' ';
    }
    cout << endl;
    return 0;
}