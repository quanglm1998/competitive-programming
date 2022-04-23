#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAGIC = 100;

int numQuery = 0;

int ask(char u, int a) {
    numQuery++;
    assert(numQuery <= 10000);
    cout << u << ' ' << a << endl;
    if (u == 'C') return 0;
    int res;
    cin >> res;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> p(n + 1, 0);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= n; j += i) {
                p[j] = 1;
            }
        }
    }
    vector<int> has(n + 1, 1);
    int tot = n;
    int res = 1;
    for (int i = 0; i < primes.size(); i++) {
        int u = primes[i];
        if (i % MAGIC == 0 && i && res == 1) {
            int now = ask('A', 1);
            if (now != tot) {
                for (int j = i - MAGIC; j < i; j++) {
                    if (ask('A', primes[j]) == 1) {
                        res = primes[j];
                        while (res * primes[j] <= n && ask('A', res * primes[j]) == 1) res *= primes[j];
                        break;
                    }
                }
                assert(res != 1);
            }
        }
        int expVal = 0;
        for (int j = u; j <= n; j += u) {
            expVal += has[j]; 
        }
        int now = ask('B', u);
        for (int j = u; j <= n; j += u) {
            tot -= has[j];
            has[j] = 0;
        }
        if (now != expVal) {
            if (res == 1) {
                int curId = i - 1;
                while (curId >= 0) {
                    if (ask('A', primes[curId]) == 1) {
                        res = primes[curId];
                        while (res * primes[curId] <= n && ask('A', res * primes[curId]) == 1) res *= primes[curId];
                        break;
                    }
                    curId--;
                }
                assert(res != 1);
            }
            res *= u;
            while (res * u <= n && ask('A', res * u) == 1) res *= u;
        }
    }
    if (res == 1) {
        for (int j = max(0ll, (long long)primes.size() - MAGIC); j < primes.size(); j++) {
            if (ask('A', primes[j]) == 1) {
                res *= primes[j];
                while (res * primes[j] <= n && ask('A', res * primes[j]) == 1) res *= primes[j];
            }
        }
    }
    ask('C', res);
    return 0;   
}