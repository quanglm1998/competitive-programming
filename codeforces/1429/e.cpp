#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);


    cout << bitset<10>(13) << endl;

    for (int i = 123; i < 1000000; i += 2) {
        int u = i;
        cout << "# " <<  u << ' ';
        int it = 0;
        while (u > 1) {
            it++;
            int a = u + u;
            int b = u ^ a;
            int e = ( a + u)^ (b + u);
            // while (__builtin_popcount(u) <= __builtin_popcount(e)) {
            //     // cout << u << endl;
            //     // cout << a << ' ' << b << endl;
            //     // cout << c << ' ' << d << endl;
            //     // cout << e << endl;
            //     // cout << __builtin_popcount(u) << ' ' <<  __builtin_popcount(e) << endl;
            //     // return 0;
            //     a += u;
            //     b += u;
            //     e = a ^ b;
            //     cout << e << ' ';
            // }
            u = e;
            cout << e << ' ';
            if (it >= 100) return 0;
        }
        cout << endl;
    }
    return 0;
}