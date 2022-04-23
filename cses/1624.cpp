#include <bits/stdc++.h>

using namespace std;

const int N = 8;

char s[N][N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < N; i++) cin >> s[i];
    vector<int> pos(N);
    iota(pos.begin(), pos.end(), 0);
    int res = 0;
    while (1) {
        int found = 0;
        vector<int> sum(N * 2, 0), diff(N * 2, 0);
        for (int i = 0; i < N && !found; i++) {
            if (s[i][pos[i]] == '*') found = 1;
            if (sum[i + pos[i]]) found = 1;
            else sum[i + pos[i]] = 1;
            if (diff[i - pos[i] + N]) found = 1;
            else diff[i - pos[i] + N] = 1;
        }
        res += !found;
        if (!next_permutation(pos.begin(), pos.end())) break;
    }
    cout << res << '\n';
    return 0;
}