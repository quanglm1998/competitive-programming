#include <bits/stdc++.h>

using namespace std;



void solve(int test) {
    cout << "Case #" << test << ": ";
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    
    if (n == 1) {
        if (a == b && b == c && a == 1) {
            cout << 1 << '\n';
            return;
        }
        cout << "IMPOSSIBLE\n";
        return;
    }

    a -= c;
    b -= c;

    if (a + b + c > n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    int d = n - a - b - c;

    deque<int> q;

    if (d == 0) {
        for (int i = 1; i <= c; i++) q.push_back(n);
        for (int i = 1; i <= b; i++) q.push_back(n - 1);
        for (int i = 1; i <= a; i++) q.push_front(n - 1);
    } else {
        for (int i = 1; i <= c; i++) q.push_back(n);

        if (c > 1) {
            q.pop_front();
            for (int i = 1; i <= d; i++) q.push_front(1);
            q.push_front(n);
        } else {
            if (n == 2) {
                cout << "IMPOSSIBLE\n";
                return;
            }
            if (a > 0) {
                for (int i = 1; i <= d; i++) q.push_front(1);
            } else if (b > 0) {
                for (int i = 1; i <= d; i++) q.push_back(1);
            } else {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }


        for (int i = 1; i <= b; i++) q.push_back(n - 1);
        for (int i = 1; i <= a; i++) q.push_front(n - 1);
    }

    for (int u : q) cout << u << ' ' ;
        cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}