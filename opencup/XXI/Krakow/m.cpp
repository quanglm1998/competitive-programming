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
  vector<int> a(n);
  for (auto &u : a) cin >> u;
  int p, q;
  cin >> p >> q;
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int u, int v) {
    return a[u] < a[v];
  });
  vector<long long> pref_sum(n + 1, 0);
  for (int i = 0; i < n; i++) {
    pref_sum[i + 1] = pref_sum[i] + a[order[i]];
  }
  int low = 0, high = n + 1;
  vector<int> good_ranges;
  while (high - low > 1) {
    int mid = low + high >> 1;
    vector<int> ranges;
    for (int r = mid - 1; r < n; r++) {
      if (1ll * q * mid * a[order[r]] <= (pref_sum[r + 1] - pref_sum[r - mid + 1]) * p) {
        ranges.push_back(r);
      }
    }
    if (ranges.empty()) high = mid;
    else {
      good_ranges = ranges;
      low = mid;
    }
  }
  vector<int> good(n, 0);
  auto m = low;
  // debug(m);
  // debug(good_ranges);

  for (auto r : good_ranges) {
    int low = -1, high = r + 1;
    while (high - low > 1) {
      int mid = low + high >> 1;
      // debug(mid);
      // debug(1ll * q * m * a[order[r]] + (pref_sum[r - m + 2] - pref_sum[r + 1]) * p);
      // debug(1ll * a[order[mid]] * p);
      if (1ll * q * m * a[order[r]] + (pref_sum[r - m + 2] - pref_sum[r + 1]) * p
          <= 1ll * a[order[mid]] * p) {
        high = mid;
      } else {
        low = mid;
      }
    }
    // debug(r, high);
    good[high]++;
    if (r + 1 < n) good[r + 1]--;
  }
  vector<int> res;
  for (int i = 0; i < n; i++) {
    if (i) good[i] += good[i - 1];
    if (!good[i]) res.push_back(order[i]);
  } 
  sort(res.begin(), res.end());
  cout << res.size() << '\n';
  for (auto u : res) cout << u + 1 << ' ';
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}