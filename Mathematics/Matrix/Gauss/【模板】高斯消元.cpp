#include<bits/stdc++.h>
using namespace std;

const int N = 110;
double G[N][N], x[N];
int n;

bool Gauss(){
    for(int i = 1; i <= n; i++){
        int pos = i;
        for(int j = i + 1; j <= n; j++)
            if(fabs(G[j][i]) > fabs(G[pos][i])) pos = j;
        if(fabs(G[pos][i]) < 1e-15) return false;
        if(pos != i)
            for(int j = 1; j <= n + 1; j++)
                swap(G[i][j], G[pos][j]);
        vector<int> col;
        for(int k = i; k <= n + 1; k++)
            if(fabs(G[i][k]) > 1e-15) col.push_back(k);
        for(int j = i + 1; j <= n; j++){
            double t = G[j][i] / G[i][i];
            if(fabs(G[j][i]) < 1e-15) continue;
            for(int k : col)
                G[j][k] -= G[i][k] * t;
        }
    }
    return true;
}

void solve(){
    if(!Gauss()){
		puts("No Solution");
		return;
	}
    for(int i = n; i >= 1; i--){
        x[i] = G[i][n + 1] / G[i][i];
        for(int j = 1; j < i; j++)
            G[j][n + 1] -= G[j][i] * x[i];
    }
	for(int i = 1; i <= n; i++)
		printf("%.2lf\n", x[i]);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n + 1; j++)
			scanf("%lf", &G[i][j]);
	solve();
	return 0;
}
