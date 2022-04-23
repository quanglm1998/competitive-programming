#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define x first
#define y second
int r, c;
vector<vector<int>> used;
vector<string> s;

const int X[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int Y[] = {1, 0, -1, 0, -1, 1, -1, 1};

bool inside(int u, int v) {
    return u >= 0 && u < r && v >= 0 && v < c;
}

vector<vector<int>> dis, visited;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    
    while (true) {
        cin >> r >> c;
        if (r == 0 && c == 0) {
            break;
        }

        used.assign(r, vector<int>(c, 0));
        visited.assign(r, vector<int>(c, 0));
        dis.assign(r, vector<int>(c, 0));
        s.assign(r, "");
        for (int i = 0; i < r; i++) {
            cin >> s[i];
        }
        deque<ii> dq;

        for (int i = 0; i < c; i++) {
            if (s[0][i] == '#') {
                dq.push_front({0, i});
                dis[0][i] = 0;
                used[0][i] = 1;
            } else if (s[0][i] == '.') {
                dq.push_back({0, i});
                dis[0][i] = 1;
                used[0][i] = 1;
            }
        }
        for (int i = 0; i < r; i++) {
            if (s[i][c - 1] == '#') {
                dq.push_front({i, c - 1});
                dis[i][c - 1] = 0;
                used[i][c - 1] = 1;
            } else if (s[i][c - 1] == '.') {
                dq.push_back({i, c - 1});
                dis[i][c - 1] = 1;
                used[i][c - 1] = 1;
            }
        }

        while (!dq.empty()) {
            ii foo = dq.front();
            dq.pop_front();
            int d = dis[foo.x][foo.y];

            for (int i = 0; i < 8; i++) {
                int xx = foo.x + X[i];
                int yy = foo.y + Y[i];
                if (!inside(xx, yy) || s[xx][yy] == '@' || used[xx][yy]) {
                    continue;
                }

                if (s[xx][yy] == '.') {
                    used[xx][yy] = 1;
                    dis[xx][yy] = d + 1;
                    dq.push_back({xx, yy});  
                } else {
                    used[xx][yy] = 1;
                    dis[xx][yy] = d;
                    dq.push_front({xx, yy});
                }

            }
        }

        // cout << dis[0][1] << endl;

        int mn = 1e9;

        for (int i = 0; i < r; i++) {
            if (used[i][0]) {
                mn = min(mn, dis[i][0]);
            }
        }

        for (int i = 0; i < c; i++) {
            if (used[r - 1][i]) {
                mn = min(mn, dis[r - 1][i]);
            }
        }

        cout << (mn == 1e9 ? -1 : mn) << "\n";

    }



    return 0;
}