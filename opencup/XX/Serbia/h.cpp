#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n;
int a[N], b[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;  
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    } 
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res += abs(i - a[i]);
        res += abs(i - b[i]);
    }
    cout << res << '\n';
    return 0;
}