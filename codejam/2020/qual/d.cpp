#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int b;
int s[N];
int num = 0;

int ask(int u) {
    // cerr << ++num << endl;
    cout << u << endl;
    int res;
    cin >> res;
    return res;
}

void solve(int test) {
    num = 0;
    int len = 0;
    int same = 0, diff = 0;
    for (int i = 1; i <= 150 && len * 2 < b; i += 2) {
        if (i % 10 == 1 && i > 1) { // check verdict
            if (!same) {
                if (!diff) {
                    exit(1);
                } else {
                    int u = ask(diff);
                    u = ask(diff);
                    if (u != s[diff]) {
                        reverse(s + 1, s + b + 1);
                    }
                }
            } else {
                if (!diff) {
                    int u = ask(same);
                    u = ask(same);
                    if (u != s[same]) {
                        for (int i = 1; i <= b; i++) {
                            s[i] = 1 - s[i];
                        }
                    }
                } else {
                    int u = ask(same);
                    int v = ask(diff);
                    if (u == s[same] && v == s[diff]) {
                        // do nothing   
                    } else if (u == s[same] && v != s[diff]) {
                        reverse(s + 1, s + b + 1);
                    } else if (u != s[same] && v == s[diff]) {
                        reverse(s + 1, s + b + 1);
                        for (int i = 1; i <= b; i++) {
                            s[i] = 1 - s[i];
                        }
                    } else {
                        for (int i = 1; i <= b; i++) {
                            s[i] = 1 - s[i];
                        }
                    }
                }
            }
        } else {
            len++;
            int l = len;
            int r = b - len + 1;
            s[l] = ask(l);
            s[r] = ask(r);

            if (!same && s[l] == s[r]) same = l;
            if (!diff && s[l] != s[r]) diff = l;
        }
    }
    for (int i = 1; i <= b; i++) cout << s[i];
        cout << endl;
    char ver;
    cin >> ver;
    if (ver == 'Y') exit(0);
}

int main() {
    int tc;
    cin >> tc >> b;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}