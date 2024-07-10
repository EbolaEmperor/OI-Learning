#include <bits/stdc++.h>
using namespace std;

const int N = 510;
int n, m, a[N], b[N];
int dp[N][N];
// dp[i][j]: a 结尾在 i 之前，b 结尾恰好在 j
int pre[N][N];

void output(int p){
    if(!p) return;
    output(pre[n][p]);
    printf("%d ", b[p]);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) scanf("%d", b+i);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j){
            if(a[i] == b[j]){
                dp[i][j] = 1, pre[i][j] = 0;
                for(int k = 1; k < j; ++k)
                    if(b[k] < b[j] && dp[i-1][k] + 1 > dp[i][j])
                        dp[i][j] = dp[i-1][k] + 1, pre[i][j] = k;
            } else {
                dp[i][j] = dp[i-1][j];
                pre[i][j] = pre[i-1][j];
            }
        }
    int ans = 0, ansid;
    for(int j = 1; j <= m; ++j)
        if(dp[n][j] > ans) ans = dp[n][j], ansid = j;
    printf("%d\n", ans);
    if(ans) output(ansid);
    return 0;
}