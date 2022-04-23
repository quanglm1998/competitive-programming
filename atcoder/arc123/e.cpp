#include <bits/stdc++.h>

using namespace std;

#define int long long

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
  int n;
  int ax, bx, ay, by;
  cin >> n >> ax >> bx >> ay >> by;
  if (bx == by) {
    if (ax == ay) {
      cout << n << '\n';
      return;
    } else {
      cout << 0 << '\n';
      return;
    }
  }
  if (bx > by) {
    swap(ax, ay);
    swap(bx, by);
  }

  auto GetSum = [&](int a, int b, int n) -> long long {
    long long res = 1ll * a * n;
    // debug(res);
    int foo = n / b;
    res += 1ll * b * foo * (foo - 1) / 2;
    // debug(res);
    res += 1ll * foo * (n % b);
    // debug(res);
    return res;
  };

  auto Get = [&](int l, int r) -> long long {
    if (r <= l) return 0;
    auto tot_x = GetSum(ax, bx, r) - GetSum(ax, bx, l);
    // debug(GetSum(ax, bx, r));
    // debug(GetSum(ax, bx, l));
    auto tot_y = GetSum(ay, by, r) - GetSum(ay, by, l);
    // debug(tot_x, tot_y);
    return r - l - abs(tot_x - tot_y);
  };

  int res = 0;
  for (int i = 0; i < 2; i++) {
    int l = max(1ll, (1ll * (ay - ax - 1 + i) * bx * by + by - bx - 1) / (by - bx));
    int r = min(1ll * n, (1ll * (ay - ax + i) * bx * by) / (by - bx)) + 1;
    debug(l, r);
    res += Get(l, r);
  }
  if ((1ll * (ay - ax) * bx * by) % (by - bx) == 0) {
    long long now = (1ll * (ay - ax) * bx * by) / (by - bx);
    if (now >= 1 && now <= n) res--;
  }
  cout << res << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int tc;
  cin >> tc;
  for (int test = 1; test <= tc; ++test) solve(test);
  return 0;
}