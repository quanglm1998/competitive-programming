#include <bits/stdc++.h>

using namespace std;

const int N = 10;

int n;
int x[N], y[N];
int a[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    int tot = 1;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        tot *= i;
    }
    double res = 0;
    while (1) {
        double now = 0;

        auto sq = [](int u) {
            return u * u;
        };

        for (int i = 1; i < n; i++) {
            int u = a[i];
            int v = a[i + 1];
            now += sqrt(sq(x[u] - x[v]) + sq(y[u] - y[v]));
        }
        res += now;
        if (!next_permutation(a + 1, a + n + 1)) break;
    }
    cout << fixed << setprecision(10) << res / tot << endl; 
    return 0;
}