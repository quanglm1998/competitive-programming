#include <bits/stdc++.h>

using namespace std;

// debugger, source: tourist
template <typename A, typename B>
string to_string(pair<A, B> p);
string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
  return res;
}
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

void Solve(int test) {
  string s;
  cin >> s;
  vector<int> nxt(s.size(), 0);
  for (int i = 0; i + 1 < s.size(); i++) {
    auto u = s.substr(0, i + 1);
    if (s[i + 1] == '0') u += '1';
    else u += '0';
    while (u.size() > 0 && s.substr(0, u.size()) != u) {
      u = u.substr(1);
    }
    nxt[i + 1] = u.size();
  }
  debug(nxt);
  vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1));
  for (int i = 0; i <= s.size(); i++) {
    for (int j = i - 1; j >= 0; j--) {
      dp[j][i] = dp[j + 1][i] + 2 + dp[nxt[j]][j];
      debug(j, i, dp[j][i]);
    }
  }
  cout << dp[0][s.size()] << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}