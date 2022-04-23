#include <bits/stdc++.h>

using namespace std;

int ask(string u) {
    cout << u << endl << flush;
    int res;
    cin >> res;
    if (res == 0) exit(0);
    return res;
}

int main() {
    const int N = 300;
    string fullA = "";
    for (int i = 1; i <= N; i++) fullA += 'a';
    string fullB = "";
    for (int i = 1; i <= N; i++) fullB += 'b';
    int valA = ask(fullA);
    int valB = ask(fullB);
    int n = 2 * N - valA - valB;
    string cur = "";
    int val = valA + n - N;
    for (int i = 1; i <= n; i++) cur += 'a';
    if (val == 0) {
        assert(ask(cur) == 0);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        cur[i] = 'b';
        int now = ask(cur);
        if (now < val) {
            val = now;
        } else {
            cur[i] = 'a';
        }
    }
    return 0;
}