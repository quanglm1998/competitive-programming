#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...) ;
#endif

#define sz(x) ((int) (x).size())
#define TASK "text"

const int inf = (int) 1.01e9;
const long long infll = (long long) 1.01e18;
const ld eps = 1e-9;
const ld pi = acos((ld) -1);

#ifdef DEBUG
mt19937 mrand(300); 
#else
mt19937 mrand(chrono::steady_clock::now().time_since_epoch().count()); 
#endif

int rnd(int x) {
  return mrand() % x;
}

void precalc() {
}

const int maxn = (int) 1e6 + 5;
int q;

bool read() {
  if (scanf("%d", &q) < 1) {
    return false;
  }
  return true;
}

char tmp[2][10];
int a[2 * maxn];
int l, r;
vector<pair<int, pair<int, int>>> p, np;

int getX() {
  int x = (int) tmp[1][0];
  if (x == (int) 's') {
    if (tmp[1][1] == 'i') {
      x++;
    }
  }
  return x;
}

void solve() {
  l = maxn;
  r = maxn;
  p.clear();
  for (int qq = 0; qq < q; qq++) {
    scanf("%s%s", tmp[0], tmp[1]);
    int x = getX();
    if (!qq) {
      a[r++] = x;
      p.push_back(make_pair(1, make_pair(1, 1)));
    } else {
      np.clear();
      if (tmp[0][0] == 'a') {
        a[r++] = x;
        for (int i = 0; i < sz(p); i++) {
          while (p[i].second.second) {
            int len = p[i].first;
            if (x == a[l + len]) {
              break;
            }
            p[i].first -= p[i].second.first;
            p[i].second.second--;
          }
          if (!p[i].second.second) {
            continue;
          }
          int len = p[i].first;
          len++;
          if (p[i].second.second == 1) {
            np.push_back(make_pair(len, make_pair(1, 1)));
            continue;
          }
          int len1 = p[i].first - p[i].second.first;
          if (x != a[l + len1]) {
            np.push_back(make_pair(len, make_pair(1, 1)));
            continue;
          }
          np.push_back(make_pair(len, p[i].second));
        }
        if (x == a[l]) {
          if (!np.empty() && np.back().first - np.back().second.first * np.back().second.second == 1) {
            np.back().second.second++;
          } else if (!np.empty() && np.back().second.second == 1) {
            np.back().second.first = np.back().first - 1;
            np.back().second.second++;
          } else {
            np.push_back(make_pair(1, make_pair(1, 1)));
          }
        }
      } else {
        a[--l] = x;
        for (int i = 0; i < sz(p); i++) {
          while (p[i].second.second) {
            int len = p[i].first;
            if (x == a[r - len - 1]) {
              break;
            }
            p[i].first -= p[i].second.first;
            p[i].second.second--;
          }
          if (!p[i].second.second) {
            continue;
          }
          int len = p[i].first;
          len++;
          if (p[i].second.second == 1) {
            np.push_back(make_pair(len, make_pair(1, 1)));
            continue;
          }
          int len1 = p[i].first - p[i].second.first;
          if (x != a[r - len1 - 1]) {
            np.push_back(make_pair(len, make_pair(1, 1)));
            continue;
          }
          np.push_back(make_pair(len, p[i].second));
        }
        if (x == a[r - 1]) {
          if (!np.empty() && np.back().first - np.back().second.first * np.back().second.second == 1) {
            np.back().second.second++;
          } else if (!np.empty() && np.back().second.second == 1) {
            np.back().second.first = np.back().first - 1;
            np.back().second.second++;
          } else {
            np.push_back(make_pair(1, make_pair(1, 1)));
          }
        }
      }
      swap(p, np);
    }
    int res = 0;
    cout << "# " << qq << endl;
    for (int i = l; i < r; i++) {
      cout << a[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < sz(p); i++) {
      cout << p[i].first << ' ' << p[i].second.second << ' ' << p[i].second.second << endl;
      res += p[i].second.second;
    }
    printf("%d\n", res);
  }
}

int main() {
  precalc();
#ifdef DEBUG
  assert(freopen(TASK ".in", "r", stdin));
  assert(freopen(TASK ".out", "w", stdout));
#endif
  while (read()) {
    solve();
#ifdef DEBUG
    eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}