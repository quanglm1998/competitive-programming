#include <bits/stdc++.h>

using namespace std;

class DSU {
 public:
  explicit DSU(int n) : num_comp_(n), root_(n, -1), sz_(n, 1) {}

  int num_comp() const { return num_comp_; }
  int sz(int u) { return sz_[GetRoot(u)]; }

  int GetRoot(int u) { return ~root_[u] ? root_[u] = GetRoot(root_[u]) : u; }

  bool Unite(int u, int v) {
    u = GetRoot(u);
    v = GetRoot(v);
    if (u == v) return false;
    sz_[v] += sz_[u];
    root_[u] = v;
    num_comp_--;
    return true;
  }

 private:
  int num_comp_;  // number of connected components
  vector<int> sz_;
  vector<int> root_;
};

class SuffixArray {
 public:
  const vector<int> &sa() const { return sa_; }
  const vector<int> &pos() const { return pos_; }
  const vector<int> &lcp() const { return lcp_; }

  // s can contain all type of characters, including lower case, upper case,
  // number, etc.
  // if SuffixArray is build on multiple strings (e.g. a, b, c),
  // then pass `s` as a + sep + b + sep + c in the constructor.
  // sep will be treated as a special character and won't contribute to the
  // lcp array.
  explicit SuffixArray(const string s, char sep = '\0')
      : s_(s), n_(s.size()), seperator_(sep) {
    assert(!s.empty());
    sa_.resize(n_);
    iota(sa_.begin(), sa_.end(), 0);
    pos_.resize(n_);
    for (int i = 0; i < n_; i++) pos_[i] = static_cast<int>(s_[i]);

    vector<int> temp(n_);
    vector<int> cnt(max(static_cast<int>(sizeof(char)) << 8, n_) + 1);

    auto RadixSort = [&](int offset) {
      fill(cnt.begin(), cnt.end(), 0);
      for (int i = 0; i < n_; i++) {
        cnt[i + offset < n_ ? pos_[i + offset] + 1 : 0]++;
      }
      for (int i = 1; i < cnt.size(); i++) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n_ - 1; i >= 0; i--) {
        int id = sa_[i];
        temp[--cnt[id + offset < n_ ? pos_[id + offset] + 1 : 0]] = id;
      }
      for (int i = 0; i < n_; i++) {
        sa_[i] = temp[i];
      }
    };

    int len = 1;
    auto Cmp = [&](int u, int v) {
      if (pos_[u] != pos_[v]) return pos_[u] < pos_[v];
      return (u + len < n_ && v + len < n_) ? pos_[u + len] < pos_[v + len]
                                            : u > v;
    };

    // build suffix array
    while (1) {
      RadixSort(len);
      RadixSort(0);
      temp[0] = 0;
      for (int i = 1; i < n_; i++) {
        temp[i] = temp[i - 1] + Cmp(sa_[i - 1], sa_[i]);
      }
      for (int i = 0; i < n_; i++) {
        pos_[sa_[i]] = temp[i];
      }
      if (temp[n_ - 1] + 1 == n_) break;
      len <<= 1;
    }

    // build lcp array
    lcp_.resize(n_ - 1);
    len = 0;
    for (int i = 0; i < n_; i++) {
      if (pos_[i] + 1 == n_) continue;
      int j = sa_[pos_[i] + 1];
      while (max(i, j) + len < n_ && s_[i + len] == s_[j + len] &&
             s_[i + len] != seperator_)
        len++;
      lcp_[pos_[i]] = len;
      if (len) len--;
    }
  }

 private:
  int n_;
  char seperator_;
  string s_;
  vector<int> sa_;   // index of the i-th smallest suffix of s: s[sa[i]..]
  vector<int> pos_;  // position of s[i..] in the suffix array
  vector<int> lcp_;  // longest common prefix of s[sa[i]..] and s[sa[i + 1]...]
};

void Solve(int test) {
  int n;
  cin >> n;
  string s = "";
  for (int i = 0; i < n; i++) {
    string u;
    cin >> u;
    s += u + '#';
  }
  vector<int> pos(s.size(), -1);
  int cur_pos = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '#') {
      cur_pos++;
    } else {
      pos[i] = cur_pos;
    }
  }

  SuffixArray suffix_array(s, '#');
  auto lcp = suffix_array.lcp();
  auto sa = suffix_array.sa();
  vector<int> order(s.size() - 1, 0);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int u, int v) {
    return lcp[u] > lcp[v];
  });

  DSU dsu(n);
  int res = 0;
  for (int i = 0; i < order.size() && dsu.num_comp() > 1; i++) {
    int u = order[i];
    int x = pos[sa[u]];
    int y = pos[sa[u + 1]];
    if (x == -1 || y == -1) continue;
    if (dsu.Unite(x, y)) {
      res += lcp[u];
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