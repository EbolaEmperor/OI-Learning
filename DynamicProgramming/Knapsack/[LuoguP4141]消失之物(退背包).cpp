#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
int n, m, f[N], g[N], v[N];

int main(){
    cin >> n >> m;
    f[0] = 1;
    for(int i = 1; i <= n; i++){
        cin >> v[i];
        for(int j = m; j >= v[i]; j--)
            f[j] = (f[j] + f[j - v[i]]) % 10;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            g[j] = f[j];
            if(j >= v[i]) g[j] = (g[j] - g[j - v[i]] + 10) % 10;
            if(j) printf("%d", g[j]);
        }
        printf("\n");
    }
    return 0;
}