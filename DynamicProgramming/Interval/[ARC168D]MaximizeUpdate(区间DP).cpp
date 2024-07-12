// EFR-#3-Div.2 oil
#include <bits/stdc++.h>
using namespace std;

const int N = 510;
// f[l][r]: 只轰炸 [l,r] 内的城市，至多能轰炸几次
int f[N][N];
// can[l][r][i]: 是否存在一个轰炸范围在 [l,r] 内，且能轰炸到 i 的导弹组
bool can[N][N][N];
int n, m;

void init(){
    for(int len = 2; len <= n; ++len)
        for(int l = 1; l + len - 1 <= n; ++l){
            int r = l + len - 1;
            for(int i = l; i <= r; ++i){
                if(i > l) can[l][r][i] |= can[l+1][r][i];
                if(i < r) can[l][r][i] |= can[l][r-1][i];
            }
        }
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0, l, r; i < m; ++i){
        scanf("%d%d", &l, &r);
        for(int j = l; j <= r; ++j)
            can[l][r][j] = true;
    }
    init();
    for(int len = 1; len <= n; ++len)
        for(int l = 1; l + len - 1 <= n; ++l){
            int r = l + len - 1;
            // 枚举 [l,r] 中最后一个被轰炸的城市 i
            for(int i = l; i <= r; ++i)
                if(can[l][r][i]) f[l][r] = max(f[l][r], f[l][i-1] + f[i+1][r] + 1);
        }
    cout << f[1][n] << endl;
    return 0;
}