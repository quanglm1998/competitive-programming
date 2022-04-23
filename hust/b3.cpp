#include <bits/stdc++.h>

using namespace std;

const int N = 5e5;

int n;
float a[N];

int main() {
    scanf("%d", &n);
    if (n <= N) {
        for (int i = 0; i < n; i++) scanf("%f", a + i);
        sort(a, a + n);
        for (int i = 0; i < n; i++) printf("%0.2f ", a[i]);
        printf("\n"); 
        return 0;
    }
    for (int i = 0; i < N; i++) scanf("%f", a + i);
    sort(a, a + N);
    FILE* half = fopen("a.txt", "w");
    for (int i = 0; i < N; i++) fprintf(half, "%0.2f ", a[i]);
    fprintf(half, "\n");
    fclose(half);

    half = fopen("a.txt", "r");
    for (int i = N: i < n; i++) scanf("%f", a + i - N);
    return 0;
}