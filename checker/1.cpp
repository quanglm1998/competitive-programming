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

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> l(n + 1, -1), r(n + 1, -1);
  for (auto &u : a) {
    cin >> u;
  }
  for (int i = 0; i < n; i++) {
    if (l[a[i]] == -1) {
      l[a[i]] = i;
    }
    r[a[i]] = i;
  }
  vector<pair<int, int>> ranges;
  for (int i = 1; i <= n; i++) {
    if (l[i] == r[i]) continue;
    ranges.push_back({l[i], r[i]});
  }
  sort(ranges.begin(), ranges.end());
  vector<pair<int, int>> s;
  int res = 0;
  vector<int> in_s(n);
  for (auto &u : ranges) {
    if (s.empty() || u.second > s.back().second) {
      s.push_back(u);
      in_s[u.first] = in_s[u.second] = 1;
    }
  }
  vector<int> sum1(n), sum2(n);
  vector<int> banned(n);
  for (auto &u : s) {
    sum1[u.first + 1]++;
    sum1[u.second]--;
  } 
  int last = -1;
  for (auto &u : s) {
    if (u.first > last) {
      sum2[u.first + 1]++;
      sum2[u.second]--;
      last = u.second;
      banned[u.first] = banned[u.second] = 1;
    }
  }
  for (int i = 1; i < n; i++) {
    sum1[i] += sum1[i - 1];
    sum2[i] += sum2[i - 1];
  }
  for (int i = 0; i < n; i++) {
    if (banned[i]) continue;
    if (in_s[i]) {
      res += sum2[i] > 0;
    } else {
      res += sum1[i] > 0;
    }
  }
  cout << res << '\n';
  return 0;
}