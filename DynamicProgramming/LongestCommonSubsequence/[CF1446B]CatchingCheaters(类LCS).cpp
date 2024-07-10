#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int n, m;
char s1[N], s2[N];
int dp[N][N];

int main(){
    scanf("%d%d%s%s", &n, &m, s1+1, s2+1);
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j){
            if(s1[i] == s2[j]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 2);
            dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]) - 1);
            ans = max(ans, dp[i][j]);
        }
    cout << ans << endl;
    return 0;
}