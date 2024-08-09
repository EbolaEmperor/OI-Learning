#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
inline void add(int &x, const int &y){
    x += y; if(x >= ha) x -= ha;
}
inline void mns(int &x, const int &y){
    x -= y; if(x < 0) x += ha;
}
int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int mat[16][16];
int MatrixTree(int n){
	n--;
    bool swp = 0;
	for(int i = 0; i < n; i++){
		if(!mat[i][i]){
            int pos = i;
            for(int j = i + 1; j < n; j++)
                if(mat[j][i]) {pos = j; break;}
            if(!mat[pos][i]) return 0;
            for(int j = i; j < n; j++)
                swap(mat[i][j], mat[pos][j]);
            swp ^= 1;
        }
        int inv = Pow(mat[i][i], ha - 2);
		for(int j = i + 1; j < n; j++)
		{
			if(!mat[j][i]) continue;
			int t = (long long) mat[j][i] * inv % ha;
			for(int k = i; k < n; k++)
				mns(mat[j][k], (long long) t * mat[i][k] % ha);
		}
	}
	int ans = 1;
	for(int i = 0; i < n; i++)
        ans = 1ll * ans * mat[i][i] % ha;
	return swp ? ha - ans : ans;
}

int C[20][20];
void initC(){
    for(int i = 0; i <= 16; i++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % ha;
    }
}

int dsu[20];
int find(int x){return dsu[x] == x ? x : dsu[x] = find(dsu[x]);}

void work(){
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<int> g[16];
    while(m--){
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int f[16], id[16];
    memset(f, 0, sizeof(f));
    for(int s = 0; s < (1 << n); s++){
        int idcnt = 0, mrgcnt = 0;
        for(int u = 0; u < n; u++)
            if(s >> u & 1){
                dsu[idcnt] = idcnt;
                id[u] = idcnt++;
            }
        memset(mat, 0, sizeof(mat));
        for(int u = 0; u < n; u++)
            if(s >> u & 1) for(int v : g[u])
                if(s >> v & 1){
                    mat[id[u]][id[v]] = ha - 1;
                    mat[id[u]][id[u]] ++;
                    if(find(id[u]) != find(id[v]))
                        dsu[find(id[u])] = find(id[v]), mrgcnt++;
                }
        if(mrgcnt + 1 != idcnt) continue;
        int res = MatrixTree(idcnt), leaf = 0;
        for(int u = 0; u < n; u++){
            if(s >> u & 1) continue;
            int cnt = 0;
            for(int v : g[u])
                if(s >> v & 1) cnt ++;
            res = (long long) res * cnt % ha;
            leaf ++;
        }
        add(f[leaf], res);
    }
    int ans = 0;
    for(int i = k; i < n; i++){
        int tmp = (long long) C[i][k] * f[i] % ha;
        (i - k & 1) ? mns(ans, tmp) : add(ans, tmp);
    }
    printf("%d\n", ans);
}

int main(){
    initC();
    work();
    return 0;
}