#include <iostream>
#include <cstring>
using namespace std;

const int N = 110;
// f[l][r]: 删空 [l,r] 的最小代价
// g[l][r][x]: [l,r] 中允许留下 x 个 =c[r] 的数，其余删空的最小代价
int f[N][N], g[N][N][N];
int n, k, c[N];

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> c[i];
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for(int i = 1; i <= n; i++){
        f[i][i] = k - 1;
        f[i + 1][i] = 0;
        g[i][i][1] = 0;
        g[i][i][0] = k - 1;
    }
    for(int len = 2; len <= n; len++)
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            for(int i = l; i < r; i++){
                if(c[i] != c[r]) continue;
                for(int x = 1; x <= n; x++){
                    g[l][r][x] = min(g[l][r][x], g[l][i][x - 1] + f[i + 1][r - 1]);
                }
            }
            for(int i = l; i <= r; i++)
                for(int x = 1; x <= n; x++)
                    f[l][r] = min(f[l][r], g[l][i][x] + f[i + 1][r] + (x >= k ? 0 : k - x));
        }
    cout << f[1][n] << endl;
    return 0;
}