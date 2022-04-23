#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const double PI = acos(-1);

int n;
pair<int, int> a[N];
double t;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> t;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].second >> a[i].first;
    }
    sort(a + 1, a + n + 1);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        double now = 2.0 * PI * a[i].first;
        int num = floor(t / now);
        num = min(num, a[i].second);
        t -= now * num;
        res += num;
    }
    cout << res << endl;
    return 0;
}