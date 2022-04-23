#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int MAX = 100;

int n;
int a[N];
vector<int> ls;
int num[2 * N * MAX];

void solve(int test) {
    cout << "Case #" << test << ": ";
    cin >> n;
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1]; 
    }


    int minVal = *min_element(a, a + n + 1);
    int maxVal = *max_element(a, a + n + 1);
    fill(num, num + maxVal - minVal + 1, 0);

    long long res = 0;
    num[-minVal] = 1;
    for (int i = 1; i <= n; i++) {
        for (int u : ls) {
            int need = a[i] - u;
            if (need >= minVal && need <= maxVal) {
                res += num[need - minVal];
            }
            if (need < minVal) break;
        }
        num[a[i] - minVal]++;
    }

    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    int cur = 0;
    while (cur * cur < N * MAX) {
        ls.push_back(cur * cur);
        cur++;
    }
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}