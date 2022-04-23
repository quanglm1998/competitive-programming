#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int maxVal = 0;
    long long res = 0;
    for (int &u : a) {
        cin >> u;
        maxVal = max(maxVal, u);
        res += maxVal - u;
    }
    cout << res << endl;
    return 0;
}