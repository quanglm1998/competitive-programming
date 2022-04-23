#include <bits/stdc++.h>

using namespace std;

string s;

pair<int, int> inc(pair<int, int> u, pair<int, int> goodRange) {
    if (u.first == u.second && u.second == goodRange.second) return {1e9, -1e9};
    u.first++;
    u.second++;
    if (u.second > goodRange.second) u.second -= 2;
    return u;
}

pair<int, int> dec(pair<int, int> u, pair<int, int> goodRange) {
    if (u.first == u.second && u.first == goodRange.first) return {1e9, -1e9};
    u.first--;
    u.second--;
    if (u.first < goodRange.first) u.first += 2;
    return u;
}

int eval(pair<int, int> &goodRange, int delta) {
    pair<int, int> curPos(0, 0);
    for (char u : s) {
        if (u == '1') {
            curPos = inc(curPos, goodRange);
            if (curPos.first > curPos.second) {
                return 1;
            }
        } else if (u == '0') {
            curPos = dec(curPos, goodRange);
            if (curPos.first > curPos.second) {
                return -1;
            }
        } else {
            pair<int, int> curPos1 = inc(curPos, goodRange);
            pair<int, int> curPos2 = dec(curPos, goodRange);
            curPos.first = min(curPos1.first, curPos2.first);
            curPos.second = max(curPos1.second, curPos2.second);
        }
        goodRange.first = max(goodRange.first, curPos.first - delta);
        goodRange.second = min(goodRange.second, curPos.second + delta);
        // cout << "char " << u << endl;
        // cout << curPos.first << ' ' << curPos.second << endl;
        // cout << goodRange.first << ' ' << goodRange.second << endl;
    }
    return 0;
}

bool check(int delta) {
    pair<int, int> goodRange(-delta, delta);
    if (eval(goodRange, delta) != 0) return 0;
    for (int i = 0; i < 20; i++) {
        pair<int, int> now = {goodRange.first + i, min(goodRange.second, goodRange.first + i + delta)};
        if (eval(now, delta) == 0) return 1;
    }
    return 0;

    // if (delta <= 10) {
    //     for (int i = -delta; i <= 0; i++) {
    //         if (eval(i, delta) == 0) return 1;
    //         return 0;
    //     }
    // } 
    // // for (int i = -delta; i <= 0; i++) {
    // //     cout << eval(i, delta) << endl;
    // // }
    // // return 0;

    // //even
    // int low = -delta;
    // int high = 0;
    // if (low & 1) low++;
    // if (high & 1) high--;
    // while (high - low > 2) {
    //     int mid = (low + high) / 2;
    //     if (mid & 1) mid++;
    //     int val = eval(mid, delta);
    //     if (val == 0) return 1;
    //     if (val == 1) high = mid;
    //     else low = mid;
    // }
    // if (eval(low, delta) == 0 ||  eval(high, delta) == 0) return 1;

    // //odd
    // low = -delta;
    // high = 0;
    // if (low % 2 == 0) low++;
    // if (high % 2 == 0) high--;
    // while (high - low > 2) {
    //     int mid = (low + high) / 2;
    //     if (mid % 2 == 0) mid++;
    //     int val = eval(mid, delta);
    //     if (val == 0) return 1;
    //     if (val == 1) high = mid;
    //     else low = mid;
    // }
    // if (eval(low, delta) == 0 ||  eval(high, delta) == 0) return 1;
    // return 0;
}

void solve(int test) {
    cin >> s;


    int low = 0, high = s.size();

    int minVal = 0, maxVal = 0;
    int cur = 0;
    for (char u : s) {
        if (u == '?') {
            minVal = maxVal = 0;
            cur = 0;
        } else if (u == '1') {
            cur++;
            maxVal = max(maxVal, cur);
        } else {
            cur--;
            minVal = min(minVal, cur);
        }
        low = max(low, maxVal - minVal - 1);
    }

    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    // cin >> tc;
    tc = 1;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}