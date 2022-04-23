#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int X[] = {1, 0, -1, 0};
const int Y[] = {0, -1, 0, 1};
const string DIR = "RDLU";

int isSqr(int u) {
    if (u == 0) return 1;
    int v = sqrt(u);
    while (v * v > u) v--;
    while (v * v < u) v++;
    return v * v == u;
}

string getRandom() {
    string res = "";
    for (int it = 0; it < 2; it++) {
        int foo = rng() % 10;
        if (foo < 3) res += DIR[foo];
        else res += DIR[3];
    }
    return res;
}

void update(vector<pair<int, int>> &ls, string &foo, int d) {
    vector<pair<int, int>> newLs;
    pair<int, int> delta(0, 0);
    for (char u : foo) {
        int id = DIR.find(u);
        delta.first += X[id];
        delta.second += Y[id];
    }
    for (auto &u : ls) {
        u.first -= delta.first;
        u.second -= delta.second;
        for (int i = 0; i < 4; i++) {
            int x = u.first + X[i];
            int y = u.second + Y[i];
            if (x * x + y * y == d) {
                newLs.push_back({x, y});
            }
        }
    }
    ls.swap(newLs);
    sort(ls.begin(), ls.end());
    ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
    // cout << "sz " << ls.size() << endl;
    // for (auto u : ls) cout << u.first << ' ' << u.second << endl;
}

char moveHorizontal(int u) {
    if (u > 0) return 'R';
    return 'L';
}

char moveVertical(int u) {
    if (u > 0) return 'U';
    return 'D';
}

string get(pair<int, int> u) {
    int x = abs(u.first);
    int y = abs(u.second);
    string foo = "";
    for (int it = 0; it < 2; it++) {
        if (x) {
            x--;
            foo += moveHorizontal(u.first);
        } else if (y) {
            y--;
            foo += moveVertical(u.second);
        }
    }
    return foo;
}

int main() {
    ios_base::sync_with_stdio(0);
    vector<pair<int, int>> ls;
    int d = -1;
    while (d != 0) {
        if (d == -1) {
            string foo = getRandom();
            cout << foo.size() << ' ' << foo << endl;
            cin >> d;
            for (int i = 0; i * i <= d; i++) {
                int rest = d - i * i;
                if (isSqr(rest)) {
                    int u = round(sqrt(rest));
                    ls.push_back({+i, +u});
                    ls.push_back({+i, -u});
                    ls.push_back({-i, +u});
                    ls.push_back({-i, -u});
                }
            }
            sort(ls.begin(), ls.end());
            ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
            continue;
        }
        if (ls.size() == 1) {
            while (abs(ls[0].first) + abs(ls[0].second) > 4) {
                string foo = "";
                int x = abs(ls[0].first);
                int y = abs(ls[0].second);
                if (ls[0].first == 0) {
                    foo += 'L';
                    foo += moveVertical(ls[0].second);
                } else if (ls[0].second == 0) {
                    foo += 'U';
                    foo += moveHorizontal(ls[0].first);
                } else if (x < y) {
                    for (int it = 0; it < 2; it++) {
                        if (x > 1) {
                            x--;
                            foo += moveHorizontal(ls[0].first);
                        } else {
                            y--;
                            foo += moveVertical(ls[0].second);
                        }
                    }
                } else {
                    for (int it = 0; it < 2; it++) {
                        if (y > 1) {
                            y--;
                            foo += moveVertical(ls[0].second);
                        } else {
                            x--;
                            foo += moveHorizontal(ls[0].first);
                        }
                    }
                }
                cout << foo.size() << ' ' << foo << endl;
                int newD;
                cin >> newD;
                update(ls, foo, newD);
                d = newD;
            }

            // cout << "done " << ls.size() << endl;

            for (int it = 0; it < 3; it++) {
                int id = rng() % ls.size();
                string foo = get(ls[id]);
                cout << foo.size() << ' ' << foo << endl;
                int newD;
                cin >> newD;
                if (newD == 0) return 0;
                update(ls, foo, newD);
                d = newD;
            }

        } else {
            string foo = getRandom();
            cout << foo.size() << ' ' << foo << endl;
            int newD;
            cin >> newD;
            update(ls, foo, newD);
            d = newD;
        }
    }  
    return 0;
}