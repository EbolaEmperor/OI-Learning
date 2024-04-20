#include <bits/stdc++.h>
using namespace std;
 
typedef pair<int, int> pii;
const int N = 1010;
int a[N][N], t, n, k;
int f[N][N*5], num[N];
 
void getTopk(int i){
    priority_queue<pii> pq;
    pq.push(make_pair(a[1][i], -1));
    pq.push(make_pair(a[2][i], 0));
    static int it[N];
    for(int j = 1; j < i; j++){
        it[j] = 1;
        pq.push(make_pair(f[j][it[j]] + a[j+2][i], j));
    }
 
    num[i] = 0;
    for(int cycle = 1; cycle <= k; ++cycle){
        auto p = pq.top(); pq.pop();
        f[i][++num[i]] = p.first;
        int j = p.second;
        if(j > 0 && ++it[j] <= num[j])
            pq.push(make_pair(f[j][it[j]] + a[j+2][i], j));
        if(pq.empty()) break;
    }
}
 
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++)
            for(int j = i; j <= n; j++)
                scanf("%d", a[i] + j);
        
        num[1] = 2;
        f[1][1] = max(0, a[1][1]);
        f[1][2] = min(0, a[1][1]);
        for(int i = 2; i <= n; i++) getTopk(i);
 
        for(int i = 1; i <= k; ++i)
            printf("%d ", f[n][i]);
        printf("\n");
 
        for(int i = 1; i <= n; i++){
            memset(a[i], 0, sizeof(int) * (n+1));
        }
    }
    return 0;
}