#include <bits/stdc++.h>
using namespace std;

const int N = 210, mod = 100000;
int dp[N][N], n;
// big[l][r] 记录 dp[l][r] 的真实值是否 >= mod，因为有奇怪的输出要求
bool big[N][N];
char s[N];

int match(int i, int j){
    if(s[i] == '?' && s[j] == '?') return 3;
    if((s[i] == '(' || s[i] == '?') && (s[j] == ')' || s[j] == '?')) return 1;
    if((s[i] == '[' || s[i] == '?') && (s[j] == ']' || s[j] == '?')) return 1;
    if((s[i] == '{' || s[i] == '?') && (s[j] == '}' || s[j] == '?')) return 1;
    return 0;
}

int main(){
    scanf("%d%s", &n, s + 1);
    for(int i = 1; i <= n; i++) dp[i + 1][i] = 1;
    for(int len = 2; len <= n; len += 2)
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            for(int k = l + 1; k <= r; k += 2){
                long long tmp = (long long) match(l, k) * dp[l + 1][k - 1] * dp[k + 1][r];
                if(dp[l][r] + tmp >= mod || 
                   tmp != 0 && (big[l + 1][k - 1] || big[k + 1][r])) big[l][r] = 1;
                dp[l][r] = (dp[l][r] + tmp) % mod;
            }
        }
    if(big[1][n]) printf("%05d\n", dp[1][n]); // 仔细阅读题面输出要求！
    else cout << dp[1][n] << endl;
    return 0;
}