#include <bits/stdc++.h>

using namespace std;



void solve(int test) {
    cout << "Case #" << test << ": ";
    long long l, r;
    cin >> l >> r;
    long long delta = abs(l - r);
    
    long long low = 0, high = 1e10;
    while (high - low > 1) {
        long long mid = low + high >> 1;
        long long cur = mid * (mid + 1) / 2;
        if (cur <= delta) low = mid;
        else high = mid;
    }

    long long n = low;
    if (l > r) l -= n * (n + 1) / 2;
    else r -= n * (n + 1) / 2;

    int chooseLFirst = (l >= r);

    long long deltaOdd = ((n + 1) / 2) * ((n + 1) / 2);
    long long deltaEven = (n / 2) * ((n / 2) + 1);

    low = n, high = 1e10;
    while (high - low > 1) {
        long long mid = low + high >> 1;
        long long odd = ((mid + 1) / 2) * ((mid + 1) / 2) - deltaOdd;
        long long even = (mid / 2) * ((mid / 2) + 1) - deltaEven;
        if (chooseLFirst ^ (n % 2)) { // l odd
            if (odd <= l && even <= r) low = mid;
            else high = mid;
        } else { // l even
            if (odd <= r && even <= l) low = mid;
            else high = mid;
        }
    }

    long long odd = ((low + 1) / 2) * ((low + 1) / 2) - deltaOdd;
    long long even = (low / 2) * ((low / 2) + 1) - deltaEven;
    if (chooseLFirst ^ (n % 2)) { // l odd
        l -= odd;
        r -= even;    
    } else { // l even
        l -= even;
        r -= odd;
    }
    cout << low << ' ' << l << ' ' << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        solve(test);
    }
    return 0;
}