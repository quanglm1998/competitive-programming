#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i <= n; i++) {
        int u; cin >> u;
        s.insert(u);
    }   
    cout << s.size() << endl;
    return 0;
}