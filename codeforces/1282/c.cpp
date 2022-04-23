#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 200010;

int n, T, a, b;
pair<int, int> p[N];

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> T >> a >> b;
        int numEz = 0, numHard = 0;
        vector<int> vals = {0, T};
        for (int i = 1; i <= n; i++) {
            cin >> p[i].second;
            if (p[i].second) numHard++;
            else numEz++;
        }
        for (int i = 1; i <= n; i++) {
            cin >> p[i].first;
            if (p[i].first > 0) vals.push_back(p[i].first - 1);
        }
        sort(vals.begin(), vals.end());
        vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
        sort(p + 1, p + n + 1);
        int cur = 1;
        int tot = 0;
        int res = 0;
        for (auto u : vals) {
            while (cur <= n && p[cur].first <= u) {
                if (p[cur].second) {
                    numHard--;
                    tot += b;
                } else {
                    numEz--;
                    tot += a;
                }
                cur++;
            }
            if (tot > u) continue;
            int rest = u - tot;
            int now = cur - 1;
            int numA = min(rest / a, numEz);
            now += numA;
            rest -= a * numA;
            int numB = min(rest / b, numHard);
            now += numB;
            rest -= b * numB;
            res = max(res, now);
        }
        cout << res << '\n';
    }   
    return 0;
}