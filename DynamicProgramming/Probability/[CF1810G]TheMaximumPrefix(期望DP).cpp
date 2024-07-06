#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N = 5010;
int n, f[N][N], p[N];
// f[i][j]: 已经确定 a1...ai，且 [ai+1...an] 的最大前缀和为 j
//          此时的期望得分
//          当后面部分的最大前缀和为 0 时，对答案无贡献
//          因此，对于每个 k，答案就是 f[k][0]

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int main(){
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 1, x, y; i <= n; ++i){
            scanf("%d%d", &x, &y);
            p[i] = 1ll * x * Pow(y, ha - 2) % ha;
        }
        for(int i = 0; i <= n; ++i) scanf("%d", &f[0][i]);
        for(int i = 1; i <= n; ++i)
            for(int j = 0; j <= n; ++j)
                f[i][j] = (1ll * p[i] * f[i-1][j+1] + 1ll * (ha + 1 - p[i]) * f[i-1][max(0, j-1)]) % ha;
        for(int i = 1; i <= n; ++i) printf("%d ", f[i][0]);
        puts("");
        for(int i = 0; i <= n; ++i)
            memset(f[i], 0, sizeof(int) * (n+1));
    }
    return 0;
}