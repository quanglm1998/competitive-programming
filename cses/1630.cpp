#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int u;
        cin >> a[i] >> u;
        sum += u;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); i++) {
        if (i) a[i] += a[i - 1];
        sum -= a[i];
    }
    cout << sum << endl;
    return 0;
}