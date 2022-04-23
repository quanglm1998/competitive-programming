#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (st.empty()) cout << 0 << ' ';
        else cout << st.back() + 1 << ' ';
        st.push_back(i);
    }  
    cout << '\n'; 
    return 0;
}