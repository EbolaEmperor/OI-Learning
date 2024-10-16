#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 510;
char a[N], b[N];
int n, m, nxt[N], trans[N][2];
// f[i][j][k]: 串 a 匹配到第 i 个位置，其后缀部分和串 b 前缀的最长重合长度为 j， 
//             已经完整匹配到了 k 个串 b，此时的最小操作次数是多少。
int dp[N][N][N];

void get_trans(){
    nxt[0] = -1;
    for(int i = 2, j = 0; i <= m; i++){
        while(j >= 0 && b[i] != b[j + 1]) j = nxt[j];
        nxt[i] = ++j;
    }
    for(int i = 0; i < m; i++){
        int c = b[i + 1] - '0';
        trans[i][c] = i + 1;
        trans[i][c ^ 1] = trans[nxt[i]][c ^ 1];
    }
    for(int c : {0, 1}) trans[m][c] = trans[nxt[m]][c];
}

inline void upmin(int &x, const int &y){
    if(x == -1 || y < x) x = y;
}

int main(){
    scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
    get_trans();
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= m; j++)
            for(int k = 0; k <= n - m + 1; k++){
                if(dp[i][j][k] == -1) continue;
                int c = a[i + 1] - '0';
                upmin(dp[i + 1][trans[j][0]][k + (trans[j][0] == m)], 
                      dp[i][j][k] + c);
                upmin(dp[i + 1][trans[j][1]][k + (trans[j][1] == m)], 
                      dp[i][j][k] + (c ^ 1));
            }
    for(int k = 0; k <= n - m + 1; k++){
        int minans = n + 1;
        for(int j = 0; j <= m; j++)
            if(dp[n][j][k] != -1) minans = min(minans, dp[n][j][k]);
        printf("%d ", (minans == n + 1 ? -1 : minans));
    }
    return printf("\n"), 0;
}