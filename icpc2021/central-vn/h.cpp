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

#define double long double

#define EPS 1e-9
inline int cmp(double a, double b) { return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0); }
struct Point {
    double x, y;
    Point() { x = y = 0.0; }
    Point(double x, double y) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    double operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product
    double norm() { return x*x + y*y; }
    double len() { return sqrt(norm()); } // hypot(x, y);
    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

// Distance from p to Line ab
double distToLine(Point p, Point a, Point b) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    auto c = a + (ab * u);
    return (p-c).len();
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  Point a, b, c;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
  double r;
  cin >> r;
  double p;
  cin >> p;
  auto delta = distToLine(c, a, b);
  debug(delta);
  if (delta >= r) {
    cout << "NO\n";
    return 0;
  }
  auto PI = acos((double)-1.0);
  auto ratio = delta / r;
  auto w = acos(ratio);
  auto area = r * w - delta * sin(PI / 2 - w);
  area /= PI * r;
  if (area >= (p - 5) / 100 && area <= (p + 5) / 100) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
  return 0; 
}