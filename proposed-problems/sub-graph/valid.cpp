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
    registerValidation(argc, argv);

    const int N = 250000;

    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int m = inf.readInt(0, N, "n");
    ensuref(m <= 1ll * n * (n - 1) / 2, "M is to large");
    inf.readEoln();

    set<pair<int,int> > edges;

    for (int i = 1; i <= m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        if (u > v) swap(u, v);
        ensuref(u != v && !edges.count({u, v}), "Graph can't have loop or multiple edges!");
        edges.insert({u, v});   
    }

    inf.readEof();
    return 0;
}