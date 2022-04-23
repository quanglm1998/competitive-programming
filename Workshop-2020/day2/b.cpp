#include <bits/stdc++.h>

using namespace std;

pair<int, int> solve(vector<pair<int, int>> &now) {
    if (now.empty()) return {1, 1};
    pair<int, int> maxVal = *max_element(now.begin(), now.end());
    int sum = 0;
    for (auto u : now) {
        sum += u.first;
    }

    if (maxVal.first * 2 > sum) {
        int need = maxVal.first - (sum - maxVal.first);
        int have = maxVal.first - maxVal.second;
        if (need > have) need -= have;
        else {
            need %= 2;
        }
        return {sum + 1, need + 1};
    } else {
        int need = 1;
        if (sum % 2 == 1) need++;
        return {sum + 1, need};
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        string a;
        cin >> a;
        string s = "";
        for (auto u : a) {
            if (u != '1') s += u;
        }

        int num = 0;
        vector<pair<int, int>> st;
        for (auto u : s) {
            // for (auto v : st) cout << v.first << ' ' << v.second << endl;
            if (u == '2') {
                st.push_back({-1, -1});
                num++;
            } else {
                if (num == 0) {
                    continue;
                }
                num--;
                vector<pair<int, int>> now;
                int sum = 0;
                while (1) {
                    if (st.back().first == -1) break;
                    now.push_back(st.back());
                    st.pop_back();
                }
                st.pop_back();
                st.push_back(solve(now));
            }
        }
        // for (auto v : st) cout << v.first << ' ' << v.second << endl;
        vector<pair<int, int>> now;
        for (auto u : st) if (u.first != -1) now.push_back(u);
        pair<int, int> res = solve(now);
        cout << (res.first - res.second) / 2 << '\n';
    }
    return 0;
}