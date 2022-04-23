#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    map<int, int> lastPos;
    int maxVal = -1;
    int res = 0;
    for (int i = 0; i < a.size(); i++) {
        if (lastPos.count(a[i])) {
            maxVal = max(maxVal, lastPos[a[i]]);
        }
        lastPos[a[i]] = i;
        res = max(res, i - maxVal);
    } 
    cout << res << endl;
    return 0;
}