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

// 1-indexed
// Can't add when x = 0
// Ensure that T supports operator: + -
template <typename T = int>
class BIT {
 public:
  explicit BIT(int n = 0) : n_(n), t_(n + 1, T(0)) {}

  void Add(int x, T v) {
    for (; x <= n_; x += x & -x) t_[x] += v;
  }

  // [l, r] INCLUSIVELY
  void Add(int l, int r, T v) {
    assert(l <= r && l >= 0 && r <= n_);
    Add(l, v);
    Add(r + 1, -v);
  }

  T Get(int x) {
    assert(x >= 0 && x <= n_);
    T res = 0;
    for (; x; x -= x & -x) res += t_[x];
    return res;
  }

  // [l, r] INCLUSIVELY
  T Get(int l, int r) {
    assert(l <= r && r <= n_ && l >= 0);
    return Get(r) - (l ? Get(l - 1) : 0);
  }

 private:
  int n_;
  vector<T> t_;
};

template <typename T>
inline bool max_to(T &u, const T &v) { return u < v ? (u = v, true) : false; }
template <typename T>
inline bool min_to(T &u, const T &v) { return u > v ? (u = v, true) : false; }

const int N = 300010;
const int LOG = 20;

int n, m;
vector<pair<int, int>> adj[N];
vector<int> children[N];
int anc[LOG][N];
int h[N];

int min_back_edge[N];  // min height of back edge
int min_subtree[N];  // min height of back edge of subtree

void DfsInit(int u, int p) {
  h[u] = h[p] + 1;
  min_subtree[u] = min_back_edge[u] = n + 1;

  // update ancestor table
  anc[0][u] = p;
  for (int i = 1; i < LOG; i++) {
    anc[i][u] = anc[i - 1][anc[i - 1][u]];
  }
  for (auto [v, id] : adj[u]) {
    if (h[v]) {
      min_to(min_back_edge[u], h[v]);
      continue;
    }
    children[u].push_back(v);
    DfsInit(v, u);
    min_to(min_subtree[u], min_subtree[v]);
  }
  min_to(min_subtree[u], min_back_edge[u]);
}

bool is_connected_to_anc[N];
int min_val[LOG][N];
set<int> s[N];

BIT<int> t(N);
bool is_bad[N];
bool res[N];

void DfsSolve(int u) {
  // init pref and suff array
  vector<int> pref_min_subtree(children[u].size() + 1, n + 1);
  vector<int> pref_max_subtree(children[u].size() + 1, 0);
  for (int i = 0; i < children[u].size(); i++) {
    auto v = children[u][i];
    pref_min_subtree[i + 1] = min(pref_min_subtree[i], min_subtree[v]);
    pref_max_subtree[i + 1] = max(pref_max_subtree[i], min_subtree[v]);
  }
  vector<int> suff_min_subtree(children[u].size() + 1, n + 1);
  vector<int> suff_max_subtree(children[u].size() + 1, 0);
  for (int i = (int)children[u].size() - 1; i >= 0; i--) {
    auto v = children[u][i];
    suff_min_subtree[i] = min(suff_min_subtree[i + 1], min_subtree[v]);
    suff_max_subtree[i] = max(suff_max_subtree[i + 1], min_subtree[v]);
  }

  // update to child and solve
  for (int i = 0; i < children[u].size(); i++) {
    auto v = children[u][i];
    debug(u, v, pref_max_subtree[i], suff_max_subtree[i + 1]);
    if (pref_max_subtree[i] >= h[u] || suff_max_subtree[i + 1] >= h[u]) {
      is_connected_to_anc[u] = false;
    } else {
      is_connected_to_anc[u] = true;
    }
    auto now = min(pref_min_subtree[i], suff_min_subtree[i + 1]);
    min_to(now, min_back_edge[u]);
    min_val[0][u] = now;
    for (int j = 1; j < LOG; j++) {
      min_val[j][u] = min(min_val[j - 1][u], min_val[j - 1][anc[j - 1][u]]);
    }
    DfsSolve(v);
  }

  bool has_empty_child = false;

  // init
  for (auto v : children[u]) {
    debug(u, v, s[v]);
    if (s[v].empty()) has_empty_child = true;
    else if (s[v].size() == 1) {
      is_bad[*s[v].begin()] = true;
    } else {
      if (*s[v].begin() + 1 <= *s[v].rbegin() - 1) {
        t.Add(*s[v].begin() + 1, *s[v].rbegin() - 1, 1);
      }
    }
  }

  auto GetMin = [&](int u, int h) {
    int res = n + 1;
    for (int i = LOG - 1; i >= 0; i--) {
      if (h >> i & 1) {
        res = min(res, min_val[i][u]);
        u = anc[i][u];
      }
    }
    return res;
  };

  for (auto [v, id] : adj[u]) {
    if (h[v] >= h[u]) continue;
    s[u].insert(h[v]);
    debug("query", u, v, id);
    debug(is_connected_to_anc[v]);
    if (!is_connected_to_anc[v]) {
      if (children[v].size() == 2 && h[v] == 1 && h[u] == h[v] + 1 
          && children[u].empty()) {
        res[id] = true;
      } else {
        res[id] = false;
      }
      continue;
    }

    if (h[v] == 1 && h[u] == h[v] + 1 && children[v].size() == 1) {
      debug("all empty except children of u");
      if (children[u].size() == 1) {
        res[id] = true;
      } else {
        res[id] = false;
      }
      continue;
    }

    bool mid_to_high = false;

    if (GetMin(anc[0][u], h[u] - h[v] - 1) < h[v]) {
      mid_to_high = true;
    }
    if (h[v] == 1 || h[u] == h[v] + 1) mid_to_high = true;

    if (children[u].empty()) {
      debug("chilren is empty");
      res[id] = mid_to_high;
      continue;
    }

    debug(is_bad[h[v]], has_empty_child);
    if (is_bad[h[v]] || has_empty_child) {
      debug("is bad");
      res[id] = false;
      continue;
    }

    if (mid_to_high) {
      debug("mid_to_high");
      res[id] = true;
      continue;
    }

    debug(t.Get(h[v]));
    if (t.Get(h[v])) res[id] = true;
    else res[id] = false;
  }

  auto Unite = [&](set<int> &x, set<int> &y) {
    if (x.size() < y.size()) swap(x, y);
    for (auto val : y) x.insert(val);
    y.clear();
  };

  // reset
  for (auto v : children[u]) {
    if (s[v].empty()) {
      // do nothing
    } else if (s[v].size() == 1) {
      is_bad[*s[v].begin()] = false;
    } else {
      if (*s[v].begin() + 1 <= *s[v].rbegin() - 1) {
        t.Add(*s[v].begin() + 1, *s[v].rbegin() - 1, -1);
      }
    }
    Unite(s[u], s[v]);
  }

  auto Normalize = [&](set<int> &s, int h) {
    while (!s.empty() && *s.rbegin() >= h) s.erase(*s.rbegin());
  };

  Normalize(s[u], h[u] - 1);
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }
  DfsInit(1, 0);
  DfsSolve(1);
  for (int i = 1; i <= m; i++) cout << (int)res[i];
  cout << '\n';
  return 0;
}