#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n;
int h[N], l[N];
int tot = 0;

void init(int *a, vector<pair<int, int>> &hor) {
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        if (!st.empty() && a[st.back()] == a[i] && st.back() + 1 < i) hor.push_back({st.back(), i - 1});
        st.push_back(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> l[i];
    }
    vector<int> ver;
    vector<pair<int, int>> hor;
    for (int i = 1; i < n; i++) {
        tot += h[i] != h[i + 1];
        tot += l[i] != l[i + 1];
        if (h[i] != h[i + 1] && l[i] != l[i + 1]) ver.push_back(i);
    }
    init(h, hor);
    init(l, hor);
    multiset<int> s;
    sort(hor.begin(), hor.end());
    int cur = 0;
    int mm = 0;
    for (int u : ver) {
        while (cur < hor.size() && hor[cur].first <= u) {
            s.insert(hor[cur].second);
            cur++;
        }
        while (!s.empty() && *s.begin() < u) s.erase(s.begin());
        if (!s.empty()) {
            mm++;
            s.erase(s.begin());
        }
    }
    cout << tot - (ver.size() + hor.size() - mm) << '\n';
    return 0;
}