#include <bits/stdc++.h>

using namespace std;

int main() {
    int tc;
    cin >> tc;
    vector<string> ls;
    string patt = "CHO";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            string foo = "";
            foo += patt[i];
            foo += patt[j];
            ls.push_back(foo);
        }
    }
    while (tc--) {
        int n;
        cin >> n;
        ramdom_shuffle(ls.begin(), ls.end());
    }   
    return 0;
}