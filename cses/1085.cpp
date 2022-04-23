#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    long long low = *max_element(a.begin(), a.end()) - 1, high = 1e18;
    while (high - low > 1) {
        long long mid = low + high >> 1;
        long long cur = 1e18;
        int num = 0;
        for (int u : a) {
            if (cur + u > mid) {
                cur = u;
                num++;
            } else cur += u;
        }
        if (num <= k) high = mid;
        else low = mid;
    }   
    cout << high << endl;
    return 0;
}