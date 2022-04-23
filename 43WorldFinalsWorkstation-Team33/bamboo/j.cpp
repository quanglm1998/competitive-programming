#include <bits/stdc++.h>

using namespace std;

const int N = 550;
const int H = 55;
const int INF = (int)1e9 + 100;

int n, h;
int a[N][H];
vector<pair<int, int> > events;
long long sum[N];

inline long long eval(long long u, long long v, long long t) {
    return u - v * t;
}

void add(int u) {
    for (int v = 1; v <= n; v++) {
        if (u == v) continue;
        vector<int> b;
        for (int j = 1; j <= h; j++) {
            b.push_back(a[v][j]);
            b.push_back(a[u][j]);
        }
        b.push_back(INF);
        b.push_back(0);
        sort(b.begin(), b.end());
        b.resize(unique(b.begin(), b.end()) - b.begin());
        reverse(b.begin(), b.end());
        long long curU = sum[u];
        long long curV = sum[v];
        int deltaU = 0;
        int deltaV = 0;
        for (int i = 0; i + 1 < b.size(); i++) {
            while (deltaU < h && a[u][deltaU + 1] >= b[i]) deltaU++;
            while (deltaV < h && a[v][deltaV + 1] >= b[i]) deltaV++;
            long long nxtU = curU - 1ll * deltaU * (b[i] - b[i + 1]);
            long long nxtV = curV - 1ll * deltaV * (b[i] - b[i + 1]);
            if (curU < curV && nxtU < nxtV) {
                events.push_back({b[i], 1});
                events.push_back({b[i + 1], -1});
                curU = nxtU;
                curV = nxtV;
                continue;
            }
            if (curU >= curV && nxtU >= nxtV) {
                curU = nxtU;
                curV = nxtV;
                continue;
            }
            if (curU < curV) {
                assert(deltaU != deltaV);
                double t = 1.0 * (curU - curV) / (deltaU - deltaV);
                long long foo = floor(t);
                while (eval(curU, deltaU, foo) < eval(curV, deltaV, foo)) foo++;
                foo = b[i] - foo;
                foo = max(foo, 1ll * b[i + 1]);
                foo = min(foo, 1ll * b[i]);
                events.push_back({b[i], 1});
                events.push_back({foo, -1});
            } else if (nxtU < nxtV) {
                assert(deltaU != deltaV);
                double t = 1.0 * (curU - curV) / (deltaU - deltaV);
                long long foo = floor(t);
                while (eval(curU, deltaU, foo) >= eval(curV, deltaV, foo)) foo++;
                foo = b[i] - foo;
                foo = max(foo, 1ll * b[i + 1]);
                foo = min(foo, 1ll * b[i]);
                events.push_back({foo, 1});
                events.push_back({b[i + 1], -1});
            } else exit(1);

            curU = nxtU;
            curV = nxtV;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> h;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= h; j++) {
            cin >> a[i][j];
            sum[i] += a[i][j];
        }
        sort(a[i] + 1, a[i] + h + 1, greater<int>());
    }
    for (int i = 1; i <= n; i++) {
        events.clear();
        add(i);
        sort(events.begin(), events.end(), greater<pair<int, int>>());
        int best = 0;
        int cur = 0;
        for (int l = 0, r = 0; l < events.size(); l = r) {
            while (r < events.size() && events[r].first == events[l].first) r++;
            for (int i = l; i < r; i++) {
                cur += events[i].second;
            }
            best = max(best, cur);
        }
        cout << n - best << endl;
    }

    return 0;
}