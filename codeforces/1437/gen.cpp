#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    const int N = 300000;
    int tot = 0;
    int cur = 1;
    vector<int> ls;
    while ((tot + cur) <= N) {
        ls.push_back(cur);
        tot += cur;
        cur++;
    }

    ls.push_back(N - tot);
    reverse(ls.begin(), ls.end());
    cout << ls.size() << ' ' << 1 << '\n';
    for (int u : ls) {
        for (int i = 0; i < u; i++) cout << "z";
            cout << '\n';
    }
    cout << 2 << ' ';
    for (int i = 1; i <= N; i++) {
        cout << "z";
    }
    cout << '\n';
    return 0;
}