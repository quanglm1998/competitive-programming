#include "candies.h"

#include <bits/stdc++.h>

using namespace std;

const int INF = 1.01e9;

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

template <typename T>
inline bool max_to(T &u, const T &v) {
  return u < v ? (u = v, true) : false;
}

template <typename T>
inline bool min_to(T &u, const T &v) {
  return u > v ? (u = v, true) : false;
}

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l,
                                    std::vector<int> r, std::vector<int> v) {
  int n = c.size();
  int q = l.size();
  int block_size = sqrt(n);
  int num_block = (n + block_size - 1) / block_size;
  vector<vector<int>> id_in_block(num_block, vector<int>());
  vector<vector<pair<int, int>>> st(num_block, vector<pair<int, int>>());
  
  for (int i = 0; i < n; i++) {
    id_in_block[i / block_size].push_back(i);
  }
  for (int i = 0; i < num_block; i++) {
    sort(id_in_block[i].begin(), id_in_block[i].end(), [&](int u, int v) {
      return c[u] < c[v];
    });
    st[i].push_back({INF, 0});
  }

  debug(block_size, num_block);

  vector<int> a(n, 0);
  vector<long long> cur_delta(num_block, 0);
  vector<long long> min_delta(num_block, 0);
  vector<long long> max_delta(num_block, 0);

  auto UpdateStack = [&](int id, int value, int type) {
    int sum = 0;
    int last = 0;
    while (!st[id].empty()) {
      debug(st[id].size());
      if (st[id].back().second == type) {
        last = st[id].back().first;
        st[id].pop_back();
        continue;
      }
      if (sum + st[id].back().first - last > value) {
        st[id].push_back({last + value - sum, type});
        break;
      }
      sum += st[id].back().first - last;
      last = st[id].back().first;
      st[id].pop_back();
    }
    if (st[id].empty()) {
      st[id].push_back({INF, type});
    }
  };

  auto UpdateBlock = [&](int id, int value) {
    debug("update block", id, value);
    if (value > 0) UpdateStack(id, value, 1);
    else UpdateStack(id, -value, 0);
    cur_delta[id] += value;
    min_to(min_delta[id], cur_delta[id]);
    max_to(max_delta[id], cur_delta[id]);
  };

  auto Commit = [&](int id) {
    int value = 0;
    int cur = 0;
    int last = 0;
    for (int i = (int)st[id].size() - 1; i >= 0; i--) {
      while (cur < (int)id_in_block[id].size() && c[id_in_block[id][cur]] < st[id][i].first) {
        int u = id_in_block[id][cur];
        int now = value + (c[u] - last) * st[id][i].second;
        a[u] = max(0ll, min_delta[id] + min(1ll * a[u], c[u] - max_delta[id])) + now;
        cur++;
      }
      value += (st[id][i].first - last) * st[id][i].second;
      last = st[id][i].first;
    }
    cur_delta[id] = min_delta[id] = max_delta[id] = 0;
    st[id].clear();
    st[id].push_back({INF, 0});
  };

  auto UpdateElement = [&](int id, int l, int r, int value) {
    debug("update", id, l, r, value);
    Commit(id);
    for (int i = l; i <= r; i++) {
      a[i] += value;
      min_to(a[i], c[i]);
      max_to(a[i], 0);   
    }
  };

  for (int i = 0; i < q; i++) {
    debug(i);
    debug(l[i], r[i], v[i]);
    int l_block = l[i] / block_size;
    int r_block = r[i] / block_size;
    if (l_block == r_block) {
      UpdateElement(l_block, l[i], r[i], v[i]);
    } else {
      if (l[i] != l_block * block_size) {
        UpdateElement(l_block, l[i], (l_block + 1) * block_size - 1, v[i]);
        l_block++;
      }
      if (r[i] != (r_block + 1) * block_size - 1) {
        UpdateElement(r_block, r_block * block_size, r[i], v[i]);
        r_block--;
      }
      for (int j = l_block; j <= r_block; j++) {
        UpdateBlock(j, v[i]);
      }
    }
    debug(st);
    debug(cur_delta);
    debug(min_delta);
    debug(max_delta);
    debug(a);
    debug(c);
  }

  for (int i = 0; i < num_block; i++) {
    Commit(i);
  }

  return a; 
}