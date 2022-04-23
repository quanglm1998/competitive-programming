#include <bits/stdc++.h>

using namespace std;

long long get(const string &s, const string &t) {
  long long res = 0;
  int cur = 0;
  int id = 0;
  vector<bool> used(s.size(), 0);
  for (int i = 0; i < t.size(); i++) {
    if (i > 0 && t[i] != t[i - 1]) {
      cur = id = 0;
    }
    while (cur < s.size()) {
      if (used[cur]) {
        cur++;
      } else if (s[cur] != t[i]) {
        cur++;
        id++;
      } else break;
    }
    res += id;
    used[cur] = 1;
    cur++;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int ord[1000];
  ord['A'] = 0;
  ord['N'] = 1;
  ord['O'] = 2;
  ord['T'] = 3;
  int tc;
  cin >> tc;
  while (tc--) {
    string s;
    cin >> s;
    string t = s;
    string res = s;
    long long tot = 0;
    int perm[] = {0, 1, 2, 3};
    while (1) {
      sort(t.begin(), t.end(), [&](char u, char v) {
        return perm[ord[u]] < perm[ord[v]];
      });
      long long now = get(s, t);
      if (now > tot) {
        tot = now;
        res = t;
      }
      if (!next_permutation(perm, perm + 4)) break;
    }
    cout << res << '\n';
  }
  return 0;
}