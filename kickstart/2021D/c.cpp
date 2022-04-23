#include <bits/stdc++.h>

using namespace std;

// source: tourist
template <typename A, typename B>
string to_string(pair<A, B> p);
 
string to_string(const string& s) {
  return '"' + s + '"';
}
 
string to_string(const char* s) {
  return to_string((string) s);
}
 
string to_string(bool b) {
  return (b ? "true" : "false");
}
 
string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}
 
template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}
 
template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
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

void solve(int test) {
  cout << "Case #" << test << ": ";
  int n, m;
  cin >> n >> m;
  set<pair<long long, long long>> s;
  for (int i = 0; i < n; i++) {
    long long l, r;
    cin >> l >> r;
    s.insert({l, r});
  }

  const long long INF = 2.01e18;

  for (int i = 0; i < m; i++) {
    // debug(i);
    // debug(s);
    long long u;
    cin >> u;
    auto it = s.lower_bound({u, INF});
    if (it != s.begin() && prev(it)->second >= u) {
      it--;
      auto val = *it;
      s.erase(it);
      cout << u << ' ';
      if (val.first < u) s.insert({val.first, u - 1});
      if (u < val.second) s.insert({u + 1, val.second});
      continue;
    }
    auto lower = -INF;
    auto upper = INF;
    if (it != s.end()) upper = it->first;
    if (it != s.begin()) lower = prev(it)->second;
    if (u - lower <= upper - u) {
      it--;
      auto val = *it;
      s.erase(it);
      cout << lower << ' ';
      if (val.first < val.second) s.insert({val.first, val.second - 1});
    } else {
      auto val = *it;
      s.erase(it);
      cout << upper << ' ';
      if (val.first < val.second) s.insert({val.first + 1, val.second});
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) {
    solve(test);
  }
  return 0;
}