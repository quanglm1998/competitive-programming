#include <bits/stdc++.h>

using namespace std;

int get(int n, int base) {
    if (n < base) return 0;
    return n / base + get(n / base, base);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    int num2 = get(n, 2);
    int num5 = get(n, 5);
    cout << min(num5, num2) << endl;   
    return 0;
}