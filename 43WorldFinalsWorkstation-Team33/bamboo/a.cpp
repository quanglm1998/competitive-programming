#include <bits/stdc++.h>


using namespace std;

const int N = 500010;

int n;
pair<int, int> a[N], b[N];
int idA[N], idB[N];
set<pair<int, int> > aa[N], bb[N];
int resA[N], resB[N];

bool cmpA(int u, int v) {
    if (a[u].first != a[v].first) return a[u].first < a[v].first;
    return a[u].second < a[v].second;
}

bool cmpB(int u, int v) {
    if (b[u].first != b[v].first) return b[u].first < b[v].first;
    return b[u].second < b[v].second;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].second;
        idA[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i].first;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i].second;
        idB[i] = i;
    }
    sort(idA + 1, idA + n + 1, cmpA);
    sort(idB + 1, idB + n + 1, cmpB);
    for (int l = 1, r = 1; l <= n; l = r) {
        while (r <= n && a[idA[l]].first == a[idA[r]].first) r++;
        for (int i = l; i < r; i++) {
            aa[l].insert({a[idA[i]].second, idA[i]});
        }
    }
    for (int l = 1, r = 1; l <= n; l = r) {
        while (r <= n && b[idB[l]].first == b[idB[r]].first) r++;
        for (int i = l; i < r; i++) {
            bb[l].insert({b[idB[i]].second, idB[i]});
        }
    }
    set<pair<int, int>> A, B;
    for (int i = 1; i <= n; i++) {
        for (auto u : aa[i]) A.insert(u);
        for (auto u : bb[i]) B.insert(u);
        assert(!A.empty());
        assert(!B.empty());
        if (A.size() < B.size()) {
            auto u = *A.begin();
            auto itV = B.lower_bound({u.first, -1});
            if (itV == B.begin()) {
                cout << "impossible" << endl;
                return 0;
            }
            itV--;
            auto v = *itV;
            resA[i] = u.second;
            resB[i] = v.second;
            A.erase(*A.begin());
            B.erase(itV);
        } else {
            auto u = * B.begin();
            auto itV = A.upper_bound({u.first + 1, -1});
            if (itV == A.end()) {
                cout << "impossible" << endl;
                return 0;
            }
            auto v = *itV;
            resA[i] = v.second;
            resB[i] = u.second;
            A.erase(itV);
            B.erase(B.begin());
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << resA[i] << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << resB[i] << ' ';
    }
    cout << endl;
    return 0;
}