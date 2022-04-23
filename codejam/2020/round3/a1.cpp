#include <bits/stdc++.h>

using namespace std;


int const MAX = 1e9 + 5;

int const N = 100;
int dp[N][N];

int max_len = 0;
pair < int, int > ans;
string res;
string s, t;
vector < int > all_chars;


int get_diff(string &p, string &q) {
    int n = p.size();
    int m = q.size();
    for (int i = 1; i < N; i++) {
        dp[0][i] = dp[i][0] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + 1;
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            if (p[i - 1] == q[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }
        }
    }

    return dp[n][m];
}


void attempt(string cur, int id) {
    if (cur != "") {
        int diff1 = get_diff(cur, s);
        int diff2 = get_diff(cur, t);
        if (ans > make_pair(diff1 + diff2, abs(diff1 - diff2))) {
            ans = make_pair(diff1 + diff2, abs(diff1 - diff2));
            res = cur;
        }
    }
    

    if (id > max_len) { 
        return;
    }
    for (char c : all_chars) {
        attempt(cur + c, id + 1);
    }
}

void solve(string s, string t) {
    res = "";
    ans = {MAX, MAX};
    max_len = min(7, (int)(s.size() + t.size()));
    set < char > chars;
    for (char c : s) {
        chars.insert(c);
    }
    for (char c : t) {
        chars.insert(c);
    }

    all_chars.clear();
    for (char c : chars) {
        all_chars.push_back(c);
    }

    attempt("", 1);
    // cout << ans.first << " " << ans.second << endl;
    cout << res << endl;
}

int main() {

    int test;
    cin >> test;
    for (int test_case = 1; test_case <= test; test_case++) {
        cout << "Case #" << test_case << ": ";
        cin >> s >> t;
        solve(s, t);

    }
}