#include<bits/stdc++.h>
using namespace std;
const int SIZE = 500000;
int answer, n, m, k = 28;
bool choose[SIZE];
int a[SIZE], b[SIZE], deg[SIZE];
int A[30][900], B[30][900], num[30];
void dfs(int lv, int need){
    if(need >= answer)return;
    if(num[lv] == 0){
        answer = need;
        return;
    }
    for(int i = 0; i < num[lv]; i++) {
        deg[A[lv][i]] = 0;
        deg[B[lv][i]] = 0;
    }
    for(int i = 0; i < num[lv]; i++) {
        deg[A[lv][i]] ++;
        deg[B[lv][i]] ++;
    }
    int max_deg = 0, max_deg_id = 0;
    for(int i = 0; i < num[lv]; i++) {
        if(deg[A[lv][i]] > max_deg) {
            max_deg = deg[A[lv][i]];
            max_deg_id = A[lv][i];
        }
        if(deg[B[lv][i]] > max_deg) {
            max_deg = deg[B[lv][i]];
            max_deg_id = B[lv][i];
        }
    }
    if(max_deg <= 1) {
        answer = min(answer, need + num[lv]);
        return;
    }
    choose[max_deg_id] = 1;
    num[lv + 1] = 0;
    for(int i = 0; i < num[lv]; i++) {
        if(!choose[A[lv][i]] && !choose[B[lv][i]]) {
            A[lv + 1][num[lv + 1]] = A[lv][i];
            B[lv + 1][num[lv + 1]++] = B[lv][i];
        }
    }
    dfs(lv + 1, need + 1);
    choose[max_deg_id] = 0;
    num[lv + 1] = 0;
    int tmp_n = 0;
    int tmp[40];
    for(int i = 0; i < num[lv]; i++) {
        if(A[lv][i] == max_deg_id) {
            need++;
            if(need >= answer) { break; }
            tmp[tmp_n++] = B[lv][i];
            choose[B[lv][i]] = 1;
        } else if(B[lv][i] == max_deg_id) {
            need++;
            if(need >= answer) { break; }
            tmp[tmp_n++] = A[lv][i];
            choose[A[lv][i]] = 1;
        }
    }
    for(int i = 0; i < num[lv]; i++) {
        if(!choose[A[lv][i]] && !choose[B[lv][i]]) {
            A[lv + 1][num[lv + 1]] = A[lv][i];
            B[lv + 1][num[lv + 1]++] = B[lv][i];
        }
    }
    dfs(lv + 1, need);
    for(int i = 0; i < tmp_n; i++) {
        choose[tmp[i]] = 0;
    }
}
int main() {
    int base_answer = 0;
    // scanf("%d%d", &n, &m);
    n = 20000;
    m = 10000;
    answer = k + 1;
    for(int i = 0; i < m; i++) {
        // scanf("%d%d", &a[i], &b[i]);
        a[i] = i * 2;
        b[i] = i * 2 + 1;
        deg[a[i]]++;
        deg[b[i]]++;
    }
    for(int i = 0; i < n; i++) {
        if(deg[i] > k) {
            choose[i] = 1;
            base_answer++;
        }
    }
    for(int i = 0; i < m; i++) {
        if(!choose[a[i]] && !choose[b[i]]) {
            A[0][num[0]] = a[i];
            B[0][num[0]++] = b[i];
        }
    }
    if(base_answer > k || num[0] > (k + 1) * (k - base_answer)) {
        puts("-1");
        return 0;
    }
    dfs(0, base_answer);
    if(answer > k) {
        puts("-1");
    }
    else {
        printf("%d\n", n - answer);
    }
    return 0;
}