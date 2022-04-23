#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int n;
vector<int> a[N];
int trace[N * 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    if (n % 2 == 0) {
        cout << "First\n";
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << endl; 
    } else {
        cout << "Second\n";
        int sum = 0;
        vector<pair<int, int>> ls;
        for (int i = 1; i <= n * 2; i++) {
            int u;
            cin >> u;
            a[u].push_back(i);
        }

        set<int> s;
        for (int i = 1; i <= n; i++) {
            sum = (sum + a[i][0]) % (n * 2);
            s.insert(a[i][0]);
            ls.push_back({(a[i][1] - a[i][0] + n * 2) % (n * 2), i});
        }

        sort(ls.begin(), ls.end());
        memset(trace, -1,  sizeof trace);

        int need = (n * 2 - sum) % (n * 2);
        trace[0] = 0;

        vector<int> good;
        good.reserve(n * 2);
        good.push_back(0);


        int maxSum = 0;
        for (int i = 0; i < ls.size() && trace[need] == -1; i++) {
            int addVal = ls[i].first;
            int id = ls[i].second;
            if (maxSum + 1 >= addVal) {
                for (int j = maxSum + 1; j < min(n * 2, maxSum + addVal + 1) && trace[need] == -1; j++) {
                    if (trace[j] == -1) {
                        trace[j] = id;
                        good.push_back(j);
                    }
                }
                maxSum += addVal;   
            } else {
                vector<int> thisTime;
                for (auto val : good) {
                    int now = (val + addVal) % (n * 2);
                    if (trace[now] == -1) {
                        trace[now] = id;
                        thisTime.push_back(now);
                    }
                }
                for (auto u : thisTime) good.push_back(u);
            }
            while (maxSum < n * 2 - 1 && trace[maxSum + 1] != -1) maxSum++;
        }
        int cur = need;
        while (cur) {
            int id = trace[cur];
            s.erase(a[id][0]);
            s.insert(a[id][1]);
            int delta = (a[id][1] - a[id][0] + n * 2) % (n * 2);
            cur = (cur - delta + n * 2) % (n * 2);
        }
        for (int u : s) cout << u << ' ';
            cout << endl;
    }
    return 0;
}