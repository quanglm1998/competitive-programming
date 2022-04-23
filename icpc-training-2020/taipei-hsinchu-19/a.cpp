#include <bits/stdc++.h>

using namespace std;

const int N = 11;

struct Vehicle {
    pair<int, int> head;
    pair<int, int> tail;

    Vehicle() {
        head = {7, 7};
        tail = {0, 0};
    }

    void add(int u, int v) {
        head = min(head, {u, v});
        tail = max(tail, {u, v});
    }

    bool operator < (const Vehicle &o) const {
        if (head == o.head) return head < o.head;
        return tail < o.tail;
    }
};

bool check(vector<Vehicle> &now, pair<int, int> u) {
    if (u.first < 1 || u.first > 6 || u.second < 1 || u.second > 6) return 0;
    for (int i = 1; i <= 10; i++) {
        if (now[i].head.first > u.first || now[i].tail.first < u.first) continue;
        if (now[i].head.second > u.second || now[i].tail.second < u.second) continue;
        return 0;
    }
    // cout << "CHECK " << u.first << ' ' << u.second << endl;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<Vehicle> a(N);
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            int u;
            cin >> u;
            if (u != 0) {
                a[u].add(i, j);
            }
        }
    }
    int res = 11;
    map<vector<Vehicle>, int> m;
    queue<vector<Vehicle>> q;

    if (a[1].head > a[1].tail || a[1].head.first != 3) {
        cout << -1 << endl;
        return 0;
    }
    q.push(a);
    m[a] = 0;
    while (!q.empty()) {
        vector<Vehicle> u = q.front();
        q.pop();
        int cost = m[u];
        // cout << cost << endl;
        // for (int i = 1; i <= 10; i++) {
        //     cout << u[i].head.first << ' ' << u[i].head.second << ' ' << u[i].tail.first << ' ' << u[i].tail.second << endl;
        // }


        int dist = 7 - u[1].head.second;
        if (cost + dist >= res) continue;
        if (u[1].tail.second == 6) {
            res = min(res, cost + dist);
            continue;
        }
        for (int i = 1; i <= 10; i++) {
            if (u[i].head > u[i].tail) continue;
            if (u[i].head.first == u[i].tail.first) {  // horizontal
                if (check(u, make_pair(u[i].head.first, u[i].head.second - 1))) {  
                    u[i].head.second--;
                    u[i].tail.second--;
                    if (!m.count(u)) {
                        m[u] = cost + 1;
                        q.push(u);
                    }
                    u[i].head.second++;
                    u[i].tail.second++;
                }
                if (check(u, make_pair(u[i].tail.first, u[i].tail.second + 1))) {  
                    u[i].head.second++;
                    u[i].tail.second++;
                    if (!m.count(u)) {
                        m[u] = cost + 1;
                        q.push(u);
                    }
                    u[i].head.second--;
                    u[i].tail.second--;
                }
            } else { // vertical
                if (check(u, make_pair(u[i].head.first - 1, u[i].head.second))) {  
                    u[i].head.first--;
                    u[i].tail.first--;
                    if (!m.count(u)) {
                        m[u] = cost + 1;
                        q.push(u);
                    }
                    u[i].head.first++;
                    u[i].tail.first++;
                }
                if (check(u, make_pair(u[i].tail.first + 1, u[i].tail.second))) {  
                    u[i].head.first++;
                    u[i].tail.first++;
                    if (!m.count(u)) {
                        m[u] = cost + 1;
                        q.push(u);
                    }
                    u[i].head.first--;
                    u[i].tail.first--;
                }
            }
        }
    }
    if (res > 10) cout << -1 << endl;
    else cout << res << endl;
    return 0;
}