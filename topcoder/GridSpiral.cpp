#include <bits/stdc++.h>

using namespace std;

class GridSpiral {
	public:
	long long findCell(long long D) {
		if (D % 2 == 0) return -1;
        if (D < 7) return 0;
        long long val = 1;
        bool has = 0;
        int cur = 1;
        for (int i = 1; i <= (D + 1) / 2; i++) {
            val += cur;
            if (!has) {
                has = 1;
            } else {
                has = 0;
                cur++;
            }
        }
        return val - D;
	}
};


// Powered by FileEdit
