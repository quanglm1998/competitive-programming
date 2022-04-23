#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> res;

vector<int> solve(int l, int r) {
    int n = r - l + 1;
    if (n == 1) {l};
    if (n % 2 == 0) {
        vector<int> p1 = solve(l, l + n / 2 - 1);
        vector<int> p2 = solve()
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    solve(1, n);
    return 0;
}