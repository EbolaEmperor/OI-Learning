#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int sum[N], opt[N][N];
long long f[N][N];
// f[l][r]: [l,r] 区间中的数排成的最优 BST 的最小代价
// opt[l][r]: [l,r] 区间中的数排成的最优 BST 的根节点 (分界点)

long long optBST(int n){
    for(int i = 1; i <= n; i++){
        scanf("%d", &sum[i]);
        sum[i] += sum[i-1];
        f[i][i] = sum[i] - sum[i-1];
        opt[i][i] = i;
    }
    for(int len = 2; len <= n; len++){
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            f[l][r] = INT64_MAX;
            for(int k = opt[l][r-1]; k <= opt[l+1][r]; k++){
                int tmp = f[l][k-1] + f[k+1][r] + sum[r] - sum[l-1];
                if(tmp < f[l][r]){
                    f[l][r] = tmp;
                    opt[l][r] = k;
                }
            }
        }
    }
    long long ans = INT64_MAX;
    // 枚举根节点获取答案，注意不要直接用 f[1][n]，因为题目要求根节点深度为 0
    for(int i = 1; i <= n; i++)
        ans = min(ans, f[1][i-1] + f[i+1][n]);
    memset(sum, 0, sizeof(int) * (n + 1));
    for(int i = 0; i <= n + 1; i++){
        memset(f[i], 0, sizeof(long long) * (n + 1));
        memset(opt[i], 0, sizeof(int) * (n + 1));
    }
    return ans;
}

int main(){
    int n;
    while(~scanf("%d", &n))
        printf("%lld\n", optBST(n));
    return 0;
}
