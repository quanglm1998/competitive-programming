#include <bits/stdc++.h>

using namespace std;

const int N = 5;

int n;
int a[N];
int used[N][N];

int costRook() {
    int res=  0;
    memset(used, 0, sizeof used);
    while (1) {
        res++;
        pair<int, int> u = find();
        used[u.first][u.second] = 1;
        while (1) {
            pair<int, int> v;
            int cur = 100;
            for (int i = 1; i <= 4; i++) {
                
            }
        }
    }
    return res;
}

bool check() {
    int costRook = calcRook();
    int costQueen = calcQueen();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < 16; i++) a[i] = i;
    while (1) {
        if (check()) {
            for (int i = 0; i < 16; i++) {
                cout << a[i] << ' ';
                if (i % 4 == 3) cout << '\n';
            }
            return 0;
        }
        if (!next_permutation(a, a + 16)) break;
    }
    return 0;
}