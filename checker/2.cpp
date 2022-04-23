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

  int n;
int res = 0;
vector<int> c;

void Go(const vector<int> &a, int cur) {
  res = max(res, cur);
  for (int i = 0; i < n; i++) {
    if (c[i]) continue;
    for (int j = i + 1; j < n; j++) {
      if (c[j]) continue;
      for (int k = j + 1; k < n; k++) {
        if (c[k]) continue;
        if (a[i] != a[k]) continue;
        c[j] = 1;
        Go(a, cur + 1);
        c[j] = 0;
      }
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  c.resize(n);
  Go(a, 0);
  cout << res << '\n';
  return 0;
}