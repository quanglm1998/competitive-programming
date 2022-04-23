#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1010;

int n;
int x[N], y[N];
map<int, set<int>> xx, yy;

struct Data {
    int x, y;
    int len;
    vector<int> ls;
    Data(int x, int y, int len, vector<int> ls) : x(x), y(y), len(len), ls(ls) {}
};

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        xx[x[i]].insert(y[i]);
        yy[y[i]].insert(x[i]);
    }
    vector<Data> ls;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (x[i] == x[j]) {
                int newY = (y[i] + y[j]) / 2;
                vector<int> now;
                now.push_back(i);
                now.push_back(j);
                ls.emplace_back(x[i], newY, (abs(y[i] - y[j]) - 1) / 2 + 1, now);
            } else if (y[i] == y[j]) {
                int newX = (x[i] + x[j]) / 2;
                vector<int> now;
                now.push_back(i);
                now.push_back(j);
                ls.emplace_back(newX, y[i], (abs(x[i] - x[j]) - 1) / 2 + 1, now);
            } else {
                
            }
        }
    }
    return 0;
}