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
  int n;
  cin >> n;
  map<long long, int> a;
  for (int i = 0; i < 1 << n; i++) {
    int u;
    cin >> u;
    a[u]++;
  }
  while (a.size() > 1) {
    debug(a);
    map<long long, int> b;
    while (a.size() > 0) {
      auto [u, v] = *a.begin();
      a.erase(a.begin());
      if (!v) continue;
      if (a.find(u + 1) == a.end()) {
        if (v % 2) {
          cout << "NO\n";
          return;
        }
        b[u * 2] += v / 2;
      } else {
        int have = min(v, a[u + 1]);
        if ((v - have) % 2) {
          have--;
        }
        a[u + 1] -= have;
        b[u * 2 + 1] += have;
        if (v > have) b[u * 2] += (v - have) / 2;
      }
    }
    swap(a, b);
  }
  cout << "YES\n";
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}