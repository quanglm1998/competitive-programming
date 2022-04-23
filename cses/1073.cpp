#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        auto it = upper_bound(st.begin(), st.end(), u);
        if (it == st.end()) st.push_back(u);
        else *it = u;
    }
    cout << st.size() << endl;
    return 0;
}