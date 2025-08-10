#include <bits/stdc++.h>
using namespace std;

const int N = 512;
int k, n, mat[N][N];
int f[10][N][N], aux[N][N];

void solve(int lev, int l, int r) {
    if (l == r) {
        f[lev][l][l] = 0;
        return;
    }
    int mid = (l + r) / 2;
    solve(lev + 1, l, mid);
    solve(lev + 1, mid + 1, r);
    
    // f[lev][l][r] = min_{x,y} f[lev+1][l][x] + mat[x][y] + f[lev+1][y][r]
    //              = min_{y} aux[l][y] + f[lev+1][y][r]
    // where  aux[l][y] = min_{x} f[lev+1][l][x] + mat[x][y]
    for (int i = l; i <= mid; i++)
        for (int j = mid+1; j <= r; j++) {
            aux[i][j] = INT_MAX;
            for (int x = l; x <= mid; x++)
                aux[i][j] = min(aux[i][j], f[lev+1][i][x] + mat[x][j]);
        }
    for (int i = l; i <= mid; i++)
        for (int j = mid+1; j <= r; j++)
            for (int y = mid+1; y <= r; y++)
                f[lev][j][i] = f[lev][i][j] = min(f[lev][i][j], aux[i][y] + f[lev+1][y][j]);
}

int main() {
	scanf("%d", &k);
	n = (1 << k);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
    memset(f, 0x3f, sizeof(f));
    solve(0, 0, n - 1);

    int ans = INT_MAX;
    for(int l = 0; l < n/2; l++)
        for(int r = n/2; r < n; r++)
            ans = min(ans, f[0][l][r]);
    cout << ans << endl;
    return 0;
}
