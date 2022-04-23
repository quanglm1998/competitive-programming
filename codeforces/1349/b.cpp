#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 100010;

int n, k;
int a[N];
int sum[N];

bool solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n == 1) return a[0] == k;
    int flag = 1;
    for (int i = 0; i < n; i++) if (a[i] == k) flag = 0;
    if (flag) return 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= k) {
            int cnt = 0;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < k) cnt++;
                if (j - i >> 1 >= cnt) return 1;
                if (a[j] ==k) break;
            }
            cnt = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (a[j] < k) cnt++;
                if (i - j >> 1 >= cnt) return 1;
                if (a[j] == k) break;
            }
        }   
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        if (solve()) cout << "yes" << endl;
        else cout << "no" << endl;
    }   
    return 0;
}