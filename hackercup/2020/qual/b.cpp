#include <bits/stdc++.h>

using namespace std;



void solve(int test) {
    cout << "Case #" << test << ": ";
    int n;
    cin >> n;
    string s;
    cin >> s;
    int numA = 0, numB = 0;
    for (char u : s) {
        numA += u == 'A';
        numB += u == 'B';
    }
    cout << (abs(numA - numB) <= 1 ? 'Y' : 'N') << '\n';
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