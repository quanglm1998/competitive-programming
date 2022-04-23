#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int x, y;
        cin >> x >> y;
        int maxPosX, maxNegX;
        int maxPosY, maxNegY;
        maxPosX = maxNegX = 0;
        maxPosY = maxNegY = 0;
        string s;
        cin >> s;
        for (auto u : s) {
            if (u == 'U') maxPosY++;
            else if (u == 'D') maxNegY++;
            else if (u == 'R') maxPosX++;
            else maxNegX++;
        }
        bool f = 0;
        if (x >= 0) f |= maxPosX < x;
        else f |= maxNegX < (-x);
        if (y >= 0) f |= maxPosY < y;
        else f |= maxNegY < (-y);
        cout << (f ? "NO" : "YES") << '\n';
    }
    return 0;
}