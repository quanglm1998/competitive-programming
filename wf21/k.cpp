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

int p, n;
vector<int> s;
int k;
vector<pair<int, int>> add, del;
vector<bool> used_island;
set<int> list_used;
vector<int> cnt;
vector<bool> is_dead;
vector<vector<pair<int, int>>> used_edges;
vector<set<int>> nodes_in_island;

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> p >> n;

  used_island.resize(p);
  cnt.resize(p);
  used_edges.resize(p);
  nodes_in_island.resize(p);

  s.resize(n);
  is_dead.resize(n);


  for (int i = 0; i < n; i++) {
    cin >> s[i];
    s[i]--;
    cnt[s[i]]++;
    nodes_in_island[s[i]].insert(i);
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    used_island[s[u]] = used_island[s[v]] = true;
    if (s[u] == s[v]) add.push_back({u, v});
    else del.push_back({u, v});
  }

  int delta = 0;
  vector<int> ls_delta;
  for (int i = 0; i < p; i++) {
    if (!used_island[i]) {
      delta++;
    } else {
      list_used.insert(i);
    }
  }
  for (int i = 0; i < n; i++) {
    if (!used_island[s[i]]) {
      used_island[s[i]] = true;
      ls_delta.push_back(i);
    }
  }

  int res = 0;
  vector<int> ls_res;
  for (int mask = 0; mask < (1 << del.size()); mask++) {
    for (int i = 0; i < del.size(); i++) {
      int u = (mask >> i & 1) ? del[i].first : del[i].second;
      if (!is_dead[u]) {
        is_dead[u] = true;
        cnt[s[u]]--;
        // nodes_in_island[s[u]].erase(u);
      }
    }

    debug(mask, nodes_in_island); 

    for (int mask2 = 0; mask2 < (1 << add.size()); mask2++) {
      bool failed = false;
      for (int j = 0; j < add.size(); j++) {
        if (mask2 >> j & 1) {
          if (is_dead[add[j].first] || is_dead[add[j].second]) {
            failed = true;
            break;
          }
        }
      }
      if (failed) continue;

      for (int j = 0; j < add.size(); j++) {
        if (mask2 >> j & 1) {
          used_edges[s[add[j].first]].push_back(add[j]);
        }
      }
      debug(mask2, used_edges);

      int cur = 0;
      vector<int> ls_cur;
      for (int u : list_used) {
        debug(u, used_edges[u]);
        if (used_edges[u].empty() && cnt[u]) {
          cur++;
          for (auto x : nodes_in_island[u]) {
            if (!is_dead[x]) {
              ls_cur.push_back(x);
              break;
            }
          }
        }
        vector<int> list_nodes;
        for (auto v : used_edges[u]) {
          list_nodes.push_back(v.first);
          list_nodes.push_back(v.second);
        }
        sort(list_nodes.begin(), list_nodes.end());
        list_nodes.resize(unique(list_nodes.begin(), list_nodes.end()) - list_nodes.begin());
        debug(list_nodes);
        if (list_nodes.size() * (list_nodes.size() - 1) / 2 != used_edges[u].size()) {
          failed = true;
          break;
        }
        cur += list_nodes.size();
        for (auto x : list_nodes) {
          ls_cur.push_back(x);
        }
      }

      debug(ls_cur);
      debug(res, cur);

      if (!failed) {
        if (res < cur) {
          res = cur;
          ls_res = ls_cur;
        }
      }

      for (int j = 0; j < add.size(); j++) {
        if (mask2 >> j & 1) {
          used_edges[s[add[j].first]].clear();
        }
      }
    }

    for (int i = 0; i < del.size(); i++) {
      int u = (mask >> i & 1) ? del[i].first : del[i].second;
      if (is_dead[u]) {
        is_dead[u] = false;
        cnt[s[u]]++;
        // nodes_in_island[s[u]].insert(u);
      }
    }
  }
  cout << res + delta << '\n';
  for (auto u : ls_delta) cout << u + 1 << ' ';
  for (auto u : ls_res) cout << u + 1 << ' ';
  cout << '\n';
  return 0;
}