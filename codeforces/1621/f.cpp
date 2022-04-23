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
  int n, a, b, c;
  cin >> n >> a >> b >> c;
  string s;
  cin >> s;
  int num[2] = {0, 0};
  vector<int> ls;
  int num_pos[2] = {0, 0};
  for (int l = 0, r = 0; l < n; l = r) {
    while (r < n && s[l] == s[r]) {
      r++;
    }
    num[s[l] - '0'] += r - l - 1;
    num_pos[s[l] - '0'] += r - l;
    if (s[l] == '0' && l != 0 && r != n) {
      ls.push_back(r - l - 1);
    }
  }
  debug(num[0], num[1]);
  sort(ls.begin(), ls.end());
  for (int i = 1; i < ls.size(); i++) {
    ls[i] += ls[i - 1];
  }
  debug(ls);
  long long res = -1e18;
  int min_val = min(num[0], num[1]);
  // end with 0
  {
    res = max(res, 1ll * min_val * (a + b) + (num[0] > min_val) * a);
  }
  // end with 1
  {
    for (int i = 0; i <= min_val; i++) {
      long long tot = 1ll * i * (a + b) + (num[1] > i) * b;
      res = max(res, tot);
      if (b > c) {
        int num_zero = num_pos[0];
        int can = upper_bound(ls.begin(), ls.end(), i) - ls.begin();
        tot += 1ll * can * (b - c);
        num_zero -= i + can;
        can = min(num_zero, max(0, num[1] - i - 1));
        tot += 1ll * can * (b - c);
        res = max(res, tot);
      }
    }
  }
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}