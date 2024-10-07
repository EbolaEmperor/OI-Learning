#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N = 55, L = 10005;
// f[i][j][k]: 前 i 只猫，分成 j 组，总长度为 k 的方案数
int f[N][N][L], h[N], n, l;
int C[L+N][N];

void initC(){
    for(int i = 0; i <= n + l; i++){
        C[i][0] = 1;
        for(int j = 1; j <= n && j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % ha;
    }
}

inline void add(int &x, const int &y){
    x = (x + y >= ha) ? (x + y - ha) : (x + y);
}

int main() {
    cin >> n >> l;
    for(int i = 1; i <= n; i++) cin >> h[i];
    sort(h + 1, h + 1 + n);
    f[1][1][1] = 1;
    for(int i = 1; i < n; i++)
        for(int j = 1; j <= i; j++)
            for(int k = i; k <= l; k++){
                if(!f[i][j][k]) continue;
                if(k + h[i + 1] <= l)
                    add(f[i + 1][j][k + h[i + 1]], 2ll * j * f[i][j][k] % ha); //加入某个已有组
                if(k < l && j < n)
                    add(f[i + 1][j + 1][k + 1], f[i][j][k]); // 另起一组
                if(j > 1 && k + 2 * h[i + 1] - 1 <= l)
                    add(f[i + 1][j - 1][k + 2 * h[i + 1] - 1], 
                        (long long) j * (j - 1) * f[i][j][k] % ha); // 缝合两个已有组
            }
    initC();
    int ans = 0;
    for(int k = n; k <= l; k++)
        ans = (ans + (long long) f[n][1][k] * C[l-k+n][n]) % ha;
    cout << ans << endl;
    return 0;
}
