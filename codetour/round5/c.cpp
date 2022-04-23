#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }   
    long long res = 0;
    long long totMax = 0;
    long long totMin = 0;
    vector<pair<int, int>> stMax, stMin;
    for (int i = 1; i <= n; i++) {
        int len = 1;
        while (!stMax.empty() && stMax.back().first <= a[i]) {
            len += stMax.back().second;
            totMax -= 1ll * stMax.back().second * stMax.back().first * stMax.back().first;
            stMax.pop_back();
        }
        stMax.push_back({a[i], len});
        totMax += 1ll * a[i] * a[i] * len;

        len = 1;
        while (!stMin.empty() && stMin.back().first >= a[i]) {
            len += stMin.back().second;
            totMin -= 1ll * stMin.back().second * stMin.back().first * stMin.back().first;
            stMin.pop_back();
        }
        stMin.push_back({a[i], len});
        totMin += 1ll * a[i] * a[i] * len;
        res += totMax - totMin;
    }
    cout << res << endl;
    return 0;
}