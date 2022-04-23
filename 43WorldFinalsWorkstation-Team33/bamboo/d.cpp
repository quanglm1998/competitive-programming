#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 6;

int id[N];
int val[N];
int sum[N];
int pref[N];
int range_sum[N];
vector<int> a[N];

int n;

deque<int> M[N];

int ok(int id) {
    return range_sum[id] == 0 && !M[id].empty() && sum[M[id][0]] + pref[id] >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        char t; int ID;
        cin >> t >> ID;
        val[i] = t == 's' ? +1 : -1;
        id[i] = ID;
        range_sum[ID] += val[i];
        sum[i] = range_sum[id[i]];
        a[ID].push_back(i);
    }

    for (int i = n + 1; i <= n + n; ++i) {
        val[i] = val[i - n];
        id[i] = id[i - n];
        sum[i] = range_sum[id[i]] + val[i];
        range_sum[id[i]] += val[i];
    }
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            while (!M[i].empty() && sum[M[i].back()] >= sum[a[i][j]]) M[i].pop_back();
            M[i].push_back(a[i][j]);
        }
        pref[i] = 0;
    }

    int bestcut = 1;
    int cur_ans = 0;
    int ans = 0;
    for (int i = 1; i < N; ++i) {
        if (ok(i)) {
            cur_ans += 1;
            //cerr << "init " << i << ' ' << range_sum[i] << endl;
        }
    }
    ans = cur_ans;

    //cerr << "init " << cur_ans << endl;
    //for (int i = 1; i <= 2; ++i) cerr << i << ' ' << range_sum[i] << ' ' << sum[M[i][0]] + pref[i] << endl;

    for (int i = 1; i < n; ++i) {
        int x = ok(id[i]);

        pref[id[i]] -= val[i];
        if (!M[id[i]].empty() && M[id[i]][0] == i) M[id[i]].pop_front();

        while (!M[id[i + n]].empty() && sum[M[id[i + n]].back()] >= sum[i + n]) {
            M[id[i + n]].pop_back();
        }
        M[id[i + n]].push_back(i + n);

        cur_ans += ok(id[i]) - x;
        if (ans < cur_ans) {
            ans = cur_ans;
            bestcut = i + 1;
        }

        //cerr << "pos " << i + 1 << ' ' << cur_ans << endl;
        //for (int i = 1; i <= 2; ++i) cerr << i << ' ' << range_sum[i] << ' ' << sum[M[i][0]] + pref[i] << endl;
    }

    cout << bestcut << ' ' << ans << endl;

    return 0;
}