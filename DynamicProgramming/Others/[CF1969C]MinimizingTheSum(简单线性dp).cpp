#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
// f[i][j]: 前 i 个数用了 j 次操作的最小和
long long f[N][11];
int a[N];

int main(){
    int T, n, k;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; ++i){
            scanf("%d", a + i);
            memset(f[i], 0x3f, sizeof(f[i]));
        }
        for(int i = 1; i <= n; ++i)
            for(int j = 0; j <= min(i-1,k); ++j){
                int mna = a[i];
                for(int d = 0; d <= j; ++d){
                    f[i][j] = min(f[i][j], f[i-d-1][j-d] + (long long) mna * (d+1));
                    mna = min(mna, a[i-d-1]);
                }
            }
        printf("%lld\n", (n > k) ? f[n][k] : f[n][n-1]);
    }
    return 0;
}