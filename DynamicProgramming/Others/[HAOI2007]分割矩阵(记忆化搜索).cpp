#include <bits/stdc++.h>
using namespace std;

const int N = 12;
int r, c, n;
double xbar;
int a[N][N], s[N][N];
double f[N][N][N][N][N];
bool vis[N][N][N][N][N];

double sum(int i1, int j1, int i2, int j2){
    return s[i2][j2] - s[i1-1][j2] - s[i2][j1-1] + s[i1-1][j1-1];
}

double dfs(int i1, int j1, int i2, int j2, int k){
    if(k == 1) return pow(sum(i1,j1,i2,j2) - xbar, 2);
    if(vis[i1][j1][i2][j2][k]) return f[i1][j1][i2][j2][k];
    double ans = 1e12;
    for(int i = i1; i < i2; ++i) // 沿行切割
        for(int v = 1; v < k; ++v)
            ans = min(ans, dfs(i1,j1,i,j2,v) + dfs(i+1,j1,i2,j2,k-v));
    for(int j = j1; j < j2; ++j) // 沿列切割
        for(int v = 1; v < k; ++v)
            ans = min(ans, dfs(i1,j1,i2,j,v) + dfs(i1,j+1,i2,j2,k-v));
    vis[i1][j1][i2][j2][k] = 1;
    return f[i1][j1][i2][j2][k] = ans;
}

int main(){
    cin >> r >> c >> n;
    for(int i = 1; i <= r; ++i)
        for(int j = 1; j <= c; ++j){
            cin >> a[i][j];
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
        }
    xbar = (double)s[r][c] / n;
    double ans = dfs(1, 1, r, c, n);
    printf("%.2lf\n", sqrt((double)ans / n));
    return 0;
}