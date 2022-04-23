#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> getPrimeDivs(int u) {
    vector<pair<int, int>> res;
    for (int i = 2; i * i <= u; i++) {
        if (u % i == 0) {
            int cnt = 0;
            while (u % i == 0) {
                u /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }
    if (u > 1) res.push_back({u, 1});
    return res;
}

vector<int> getDivs(vector<pair<int, int>> primeDivs) {
    vector<int> res(1, 1);
    for (auto u : primeDivs) {
        int sz = res.size();
        for (int i = 1, now = u.first; i <= u.second; i++, now *= u.first) {
            for (int j = 0; j < sz; j++) res.push_back(res[j] * now);
        }
    }
    res.erase(res.begin());
    return res;   
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<pair<int, int>> primeDivs = getPrimeDivs(n);
        if (primeDivs.size() == 1) {
            vector<int> divs = getDivs(primeDivs);
            for (int u : divs) cout << u << ' ';
            cout << "\n0\n";
        } else if (primeDivs.size() == 2) {
            if (n == primeDivs[0].first * primeDivs[1].first) {
                cout << primeDivs[0].first << ' ' << primeDivs[1].first << ' ' << n << '\n';
                cout << 1 << '\n';
            } else {
                list<int> res;
                vector<list<int>::iterator> pos(2);
                res.push_front(primeDivs[0].first);
                pos[0] = res.begin();
                res.push_front(primeDivs[1].first);
                pos[1] = res.begin();
                res.insert(pos[0], primeDivs[0].first * primeDivs[1].first);
                res.insert(pos[1], n);
                vector<int> divs = getDivs(primeDivs);
                for (int u : divs) {
                    if (u == primeDivs[0].first) continue;
                    if (u == primeDivs[1].first) continue;
                    if (u == primeDivs[0].first * primeDivs[1].first) continue;
                    if (u == n) continue;
                    if (u % primeDivs[0].first == 0) res.insert(pos[0], u);
                    else res.insert(pos[1], u);
                }
                for (int u : res) cout << u << ' ';
                    cout << "\n0\n";
            }
        } else {
            list<int> res;
            vector<list<int>::iterator> pos(primeDivs.size());
            set<int> s;
            for (int i = 0; i < primeDivs.size(); i++) {
                res.push_front(primeDivs[i].first);
                pos[i] = res.begin();
                s.insert(primeDivs[i].first);
                if (i >= 1) {
                    res.insert(pos[i - 1], primeDivs[i].first * primeDivs[i - 1].first);
                    s.insert(primeDivs[i].first * primeDivs[i - 1].first);
                }
            }
            res.insert(pos.back(), primeDivs[0].first * primeDivs.back().first);
            s.insert(primeDivs[0].first * primeDivs.back().first);
            vector<int> divs = getDivs(primeDivs);
            for (int u : divs) {
                if (s.find(u) != s.end()) continue;
                for (int i = 0; i < primeDivs.size(); i++) {
                    if (u % primeDivs[i].first == 0) {
                        res.insert(pos[i], u);
                        break;
                    }
                }
            }
            for (int u : res) cout << u << ' ';
                cout << "\n0\n";
        }
    }
    return 0;
}