#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    int numL = 0, numR = 0;
    for (int i = 1; i <= n; i++) {
        char u; cin >> u;
        if (u == 'L') numL++;
        else numR++;
    }      
    cout << numL + numR + 1 << endl;
    return 0;
}