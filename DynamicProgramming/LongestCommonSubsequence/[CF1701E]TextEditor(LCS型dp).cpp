#include <iostream>
#include <cstring>
using namespace std;

const int N = 5010;
int dp[3][2][N];
// dp[0/1/2][i][j]: 当前在 左/中/右 段，s[i] 与 t[j] 匹配，
//                  前 i 个字母对操作次数的最小贡献。
//                  其中 i 用滚动数组优化。
char s[N], t[N];

int work(){
    int n, m;
    scanf("%d%d%s%s", &n, &m, s+1, t+1);
    for(int k = 0; k < 3; k++)
        for(int i = 0; i < 2; i++)
            memset(dp[k][i], 0x3f, sizeof(int) * (m + 1));
    dp[1][0][0] = dp[2][0][0] = 0;
    dp[0][0][0] = 1; // 如果有左段，则必须有一次 Home 操作
    for(int i = 1, p = 1; i <= n; i++, p ^= 1){
        for(int j = 0; j <= m; j++){
            // 不让 s[i] 与 t[j] 匹配
            dp[0][p][j] = dp[0][p^1][j] + 2;
            dp[1][p][j] = 0x3f3f3f3f;
            dp[2][p][j] = min(dp[1][p^1][j], dp[2][p^1][j]) + 1;
            // 尝试令 s[i] 与 t[j] 匹配
            if(j && s[i] == t[j]){
                dp[0][p][j] = min(dp[0][p][j], dp[0][p^1][j-1] + 1);
                dp[1][p][j] = min(dp[1][p][j], min(dp[0][p^1][j-1], dp[1][p^1][j-1]));
                dp[2][p][j] = min(dp[2][p][j], min(dp[1][p^1][j-1], dp[2][p^1][j-1]) + 1);
            }
        }
    }
    int ans = min(dp[0][n&1][m], min(dp[1][n&1][m], dp[2][n&1][m]));
    return (ans > 3*n) ? -1 : ans;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--) printf("%d\n", work());
    return 0;
}