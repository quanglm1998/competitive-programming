#include "testlib.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    auto n = rnd.next(opt<int>(1)) + 1;
    auto m = rnd.next(opt<int>(2)) + 1;

    m = min(1ll * m, 1ll * (n - 1) * n / 2);
    m = max(m, n - 1);

    auto t = opt<int>(3);

    cout << n << ' ' << m << '\n';

    set<pair<int, int>> s;

    for (int i = 2; i <= n; i++) {
        int u = rnd.wnext(1, i - 1, t);
        cout << u << ' ' << i << '\n';
        s.insert({u, i});
    }

    for (int i = n; i <= m; i++) {
        while (1) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u > v) swap(u, v);
            if (u != v && !s.count({u, v})) {
                s.insert({u, v});
                cout << u << ' ' << v << '\n';
                break;
            }
        }
    }
    return 0;
}