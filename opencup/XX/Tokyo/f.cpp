#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N], b[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    deque<int> st;
    long long res = 0;
    vector<int> resLs;
    for (int i = 1; i <= n; i++) {
        res += abs(a[i] - b[i]);
        bool erased = 0;
        while (!st.empty()) {
            int u = st.back();
            if (a[u] < b[u] && b[i] < a[i]) {
                if (abs(a[u] - b[u]) < abs(a[i] - b[i])) {
                    resLs.push_back(u);
                    st.pop_back();
                } else {
                    resLs.push_back(i);
                    erased = 1;
                    break;
                }
            } else break;
        }
        if (!erased) st.push_back(i);
    }
    while (!st.empty()) {
        int u = st.front();
        if (b[u] < a[u]) {
            st.pop_front();
            resLs.push_back(u);
            continue;
        }
        u = st.back();
        st.pop_back();
        resLs.push_back(u);
    }
    cout << res << '\n';
    for (int u : resLs) cout << u << ' ';
        cout << '\n';
    return 0;
}