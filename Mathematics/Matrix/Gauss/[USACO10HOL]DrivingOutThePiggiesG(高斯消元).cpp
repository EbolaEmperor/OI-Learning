#include <bits/stdc++.h>
using namespace std;

const int N = 310;
double G[N][N], x[N], deg[N];
int n, m, p, q;

bool Gauss(){
    for(int i = 1; i <= n; i++){
        int pos = i;
        for(int j = i + 1; j <= n; j++)
            if(fabs(G[j][i]) > fabs(G[pos][i])) pos = j;
        if(fabs(G[pos][i]) < 1e-15) return false;
        if(pos != i)
            for(int j = 1; j <= n + 1; j++)
                swap(G[i][j], G[pos][j]);
        for(int j = i + 1; j <= n; j++){
            double t = G[j][i] / G[i][i];
            for(int k = i; k <= n + 1; k++)
                G[j][k] -= G[i][k] * t;
        }
    }
    return true;
}

void solve(){
    assert(Gauss());
    for(int i = n; i >= 1; i--){
        x[i] = G[i][n + 1] / G[i][i];
        for(int j = 1; j < i; j++)
            G[j][n + 1] -= G[j][i] * x[i];
    }
}

int main(){
    scanf("%d%d%d%d", &n, &m, &p, &q);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v]--; G[v][u]--;
        deg[u]++; deg[v]++;
    }
    double prob = 1.0 * p / q;
    G[1][n + 1] = prob;
    for(int i = 1; i <= n; i++){
        G[i][i] = 1;
        for(int j = 1; j <= n; j++)
            if(j != i && G[i][j]) G[i][j] = G[i][j] / deg[j] * (1 - prob);
    }
    solve();
    for(int i = 1; i <= n; i++)
        printf("%.9lf\n", x[i]);
    return 0;
}