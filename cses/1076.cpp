#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/*
    change null_type to int if we want to use map instead
    find_by_order(k) returns the k-th element (0-indexed)
    order_of_key(k) returns numbers of item being strictly smaller than k
*/


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &u : a) cin >> u;
    ordered_set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        s.insert({a[i], i});
        if (i >= k) s.erase({a[i - k], i - k});
        if (i >= k - 1) {
            cout << s.find_by_order((k - 1) / 2)->first << ' ';
        }
    }
    cout << endl;
    return 0;
}