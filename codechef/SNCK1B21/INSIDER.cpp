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

vector<int> Solve(const vector<int> &a) {
  auto n = a.size();

  vector<int> b = a;
  for (int i = 0; i < n; i++) b.push_back(a[i] + 1);
  sort(b.begin(), b.end());
  b.resize(unique(b.begin(), b.end()) - b.begin());
  map<int, vector<int>> m;
  for (int i = 0; i < n; i++) {
    m[a[i]].push_back(i);
  }
  set<pair<pair<int, int>, bool>> s;
  s.insert({{0, n - 1}, 1});
  int sz = 1;
  vector<pair<int, int>> res;

  auto Add = [&](int u) {
    auto it = s.lower_bound({{u, -1}, 0});
    bool same_left = false;
    bool same_right = false;
    if (it != s.end() && it->second == 0) {
      same_right = true;
    }
    if (it != s.begin() && prev(it)->second == 0) {
      same_left = true;
    }

    bool has_left = false;
    bool has_right = false;
    if (it != s.end()) has_right = true;
    if (it != s.begin()) has_left = true;

    if (!same_right && !same_left && has_left && has_right) {
      sz += 2;
    } else if (!same_left && !same_right) {
      sz++;
    }

    pair<pair<int, int>, int> cur = {{u, u}, 0};
    if (it != s.end() && it->first.first == u + 1 && it->second == 0) {
      auto foo = *it;
      s.erase(foo);
      cur.first.second = foo.first.second;
    }
    it = s.lower_bound(cur);
    if (it != s.begin() && prev(it)->first.second + 1 == u && prev(it)->second == 0) {
      auto foo = *prev(it);
      s.erase(prev(it));
      cur.first.first = foo.first.first;
    }
    s.insert(cur);
  };

  auto Remove = [&](int u) {
    auto it = s.lower_bound({{u + 1, u}, 0});
    assert(it != s.begin());
    it--;
    auto foo = *it;
    s.erase(it);
    if (foo.first.first < u && u < foo.first.second) {
      s.insert({{foo.first.first, u - 1}, 1});
      s.insert({{u + 1, foo.first.second}, 1});
    } else if (foo.first.first < u) {
      s.insert({{foo.first.first, u - 1}, 1});
    } else if (u < foo.first.second) {
      s.insert({{u + 1, foo.first.second}, 1});
    } else {
      auto it = s.lower_bound(foo);
      if (it != s.end() && it->second == 0) sz--;
      if (it != s.begin() && prev(it)->second == 0) sz--;
      if (s.empty()) sz = 0;
    }
  };

  debug(m);

  vector<int> last;
  for (auto u : b) {
    debug("update", u);
    for (auto pos : last) {
      Add(pos);
      debug("add", pos);
      debug(sz, s);
    }
    auto nxt = m[u];
    for (auto pos : nxt) {
      Remove(pos);
      debug("remove", pos);
      debug(sz, s);
    }
    if (sz > 1) {
      if (res.empty() || res.back().second < sz) {
        res.push_back({u, sz});
      }
    }

    last.swap(nxt);
  }

  debug(res);

  vector<int> ans(n - 1, -1e9);
  int ptr = 0;
  for (int i = 0; i < ans.size(); i++) {
    while (ptr < res.size() && i + 2 > res[ptr].second) ptr++;
    if (ptr == res.size()) break;
    ans[i] = res[ptr].first;
  }
  return ans;
}

void Solve(int test) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &u : a) {
    cin >> u;
  }
  auto b = Solve(a);
  for (auto &u : a) {
    u = -u;
  }
  auto c = Solve(a);
  for (auto u : b) {
    cout << (u == -1e9 ? -1 : u) << ' ';
  }
  cout << '\n';
  for (auto u : c) {
    cout << (u == -1e9 ? -1 : -u) << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) Solve(test);
  return 0;
}