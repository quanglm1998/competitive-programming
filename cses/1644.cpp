#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, A, B;
    cin >> n >> A >> B;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    multiset<long long> s;
    vector<long long> sumPref(n + 1, 0);
    long long res = -1e18;
    for (int i = 1; i <= n; i++) {
        sumPref[i] = a[i] + sumPref[i - 1];
        if (i - A >= 0) s.insert(sumPref[i - A]);
        if (i - B >= 1) s.erase(s.find(sumPref[i - B - 1]));
        if (!s.empty()) res = max(res, sumPref[i] - *s.begin());
    }
    cout << res << endl;
    return 0;
}