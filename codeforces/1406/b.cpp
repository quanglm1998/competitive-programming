#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const long long INF = 1e18;

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
        vector<long long> minVal(6, INF), maxVal(6, -INF);
        minVal[0] = maxVal[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 4; j >= 0; j--) {
                if (abs(minVal[j]) != INF) {
                    minVal[j + 1] = min(minVal[j + 1], minVal[j] * a[i]);
                    maxVal[j + 1] = max(maxVal[j + 1], minVal[j] * a[i]);
                }
                if (abs(maxVal[j]) != INF) {
                    minVal[j + 1] = min(minVal[j + 1], maxVal[j] * a[i]);
                    maxVal[j + 1] = max(maxVal[j + 1], maxVal[j] * a[i]);
                }
            }
        }
        cout << maxVal[5] << '\n';
    }
    return 0;
}