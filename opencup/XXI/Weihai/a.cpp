#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

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

int n, m;
vector<int> adj[N];
pair<int, int> edges[N];
vector<vector<int>> res;
pair<int, int> id[N];
int used[N];

vector<int> GetList(int x, int y) {
  fill(used + 1, used + n + 1, 0);
  used[x] = 1;
  used[y] = 2;
  queue<int> q;
  q.push(x);
  q.push(y);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (used[v]) continue;
      used[v] = used[u];
      q.push(v);
    }
  }
  vector<int> res;
  for (int i = 1; i <= n; i++) {
    if (used[i] == 1) res.push_back(i);
  }
  return res;
}


int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges[i] = {u, v};
  }

  int min_deg_node = 0;
  for (int i = 1; i <= n; i++) {
    if (!min_deg_node || adj[min_deg_node].size() > adj[i].size()) {
      min_deg_node = i;
    }
  }


  struct custom_hash {
      static uint64_t splitmix64(uint64_t x) {
          // http://xorshift.di.unimi.it/splitmix64.c
          x += 0x9e3779b97f4a7c15;
          x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
          x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
          return x ^ (x >> 31);
      }

      size_t operator()(const pair<int, int> &a) const {
          static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
          return splitmix64(1ll * a.first * 1000000000 + a.second + FIXED_RANDOM);
      }
  };

  for (auto u : adj[min_deg_node]) {
    auto ls = GetList(min_deg_node, u);
    if (n % (int)ls.size()) continue;
    if (res.size() >= n / ls.size()) continue;
    set<pair<int, int>> s;
    vector<vector<int>> cur_res(1, vector<int>());
    fill(id + 1, id + n + 1, pair(0, 0));
    for (int i = 0; i < ls.size(); i++) {
      auto v = ls[i];
      id[v] = {1, i};
      cur_res.back().push_back(v);
    }
    for (auto v : ls) {
      for (auto w : adj[v]) {
        if (id[w].first == 1) {
          auto x = id[v].second;
          auto y = id[w].second;
          if (x > y) swap(x, y);
          s.insert({x, y});
        }
      }
    }

    bool f = false; 

    int cur_layer = 2;

    debug(ls);

    while (1) {
      vector<int> nxt;
      for (auto v : cur_res.back()) {
        int clone = 0;
        for (auto w : adj[v]) {
          debug(v, w);
          if (id[w].first) continue;
          if (clone) {
            f = true;
            break;
          }
          clone = w;
        }
        if (f) break;
        if (clone) nxt.push_back(clone);
      }
      debug(nxt);
      if (nxt.empty()) break;
      if (nxt.size() != ls.size()) f = true;
      if (f) break;
      for (int i = 0; i < nxt.size(); i++) {
        auto v = nxt[i];
        id[v] = {cur_layer, i};
      }
      int num_edge = 0;
      for (auto v : nxt) {
        for (auto w : adj[v]) {
          if (id[w].first == cur_layer) {
            auto x = id[v].second;
            auto y = id[w].second;
            if (x > y) swap(x, y);
            num_edge++;
            if (!s.count({x, y})) {
              f = 1;
              break;
            }
          }
        }
        if (f) break;
      }
      if (f) break;
      if (num_edge != 2 * s.size()) {
        f = 1;
        break;
      }
      cur_res.push_back(nxt);
      cur_layer++;
    }
    if (cur_res.size() * cur_res[0].size() == n && !f) {
      if (res.size() < cur_res.size()) res = cur_res;
    }
  }
  if (res.empty()) {
    res.push_back(vector<int>(n, 0));
    iota(res.back().begin(), res.back().end(), 1);
  }
  cout << res.size() << ' ' << n / res.size() << '\n';
  for (auto u : res) {
    for (auto v : u) cout << v << ' ';
    cout << '\n';
  }
  return 0;
}