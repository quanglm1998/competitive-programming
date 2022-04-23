#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int a[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int res = 0;
        
        int minVal = 1e9, maxVal = -1e9;
        for (int i = 1; i <= n; i++) {
            if (a[i] == -1) {
                if (i + 1 <= n && a[i + 1] >= 0) {
                    minVal = min(minVal, a[i + 1]);
                    maxVal = max(maxVal, a[i + 1]);
                }
                if (i - 1 >= 1 && a[i - 1] >= 0) {
                 minVal = min(minVal, a[i - 1]);
                    maxVal = max(maxVal, a[i - 1]);   
                }
            }
        }
        if (maxVal < 0) {
            cout << 0 << ' ' << 0 << endl;
            continue;
        }
        cout << (maxVal - minVal + 1) / 2 << ' ' << minVal + (maxVal - minVal) / 2 << '\n';
    }
    return 0;
}