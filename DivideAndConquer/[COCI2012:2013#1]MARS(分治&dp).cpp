#include <bits/stdc++.h>
using namespace std;

const int N = 512;
int k, n, mat[N][N];
int f[N][N], aux[N][N];

void solve(int lev, int l, int r) {
    if (r - l == 1) {
        f[l][r] = f[r][l] = mat[l][r];
        return;
    }
    int mid = (l + r) / 2;
    solve(lev + 1, l, mid);
    solve(lev + 1, mid + 1, r);
    
    // 原始 dp 转移式：
    // f[lev][l][r] = min_{x,y} f[lev+1][l][x] + mat[x][y] + f[lev+1][y][r]
    //              = min_{y} aux[l][y] + f[lev+1][y][r]
    // where  aux[l][y] = min_{x} f[lev+1][l][x] + mat[x][y]
    // 发现不同的 lev 里用到的 [l,r] 是不同的，比如 [1,1] 就只可能在最底层用到，而 [2,3] 就只可能在倒数第三层用到
    // 所以可以把 lev 这一维压掉，但注意要加上一个 if 来判断，以免误用不属于 lev+1 层的 dp 值
    int midmid = (l + mid) / 2;
    for (int i = l; i <= mid; i++)
        for (int x = l; x <= mid; x++)
            // 这个判断是为了确保在下一层里，确实可以用 i 开头、x 结束
            if (i <= midmid && x > midmid || i > midmid && x <= midmid)
                for (int j = mid+1; j <= r; j++)
                    aux[i][j] = min(aux[i][j], f[i][x] + mat[x][j]);
    midmid = (mid + 1 + r) / 2;
    for (int i = l; i <= mid; i++)
        for (int j = mid+1; j <= r; j++)
            for (int y = mid+1; y <= r; y++)
                if (j <= midmid && y > midmid || j > midmid && y <= midmid)
                    f[j][i] = f[i][j] = min(f[i][j], aux[i][y] + f[y][j]);
}

int main() {
    freopen("bitree.in", "r", stdin);
    freopen("bitree.out", "w", stdout);
	scanf("%d", &k);
	n = (1 << k);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
    memset(f, 0x3f, sizeof(f));
    memset(aux, 0x3f, sizeof(aux));
    solve(0, 0, n - 1);

    int ans = INT_MAX;
    for(int l = 0; l < n/2; l++)
        for(int r = n/2; r < n; r++)
            ans = min(ans, f[l][r]);
    cout << ans << endl;
    return 0;
}

/*
// 不压第一维的原始 dp 写法
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
*/