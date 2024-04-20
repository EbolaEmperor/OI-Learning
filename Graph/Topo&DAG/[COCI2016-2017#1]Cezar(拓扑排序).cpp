#include <bits/stdc++.h>
using namespace std;

const int N = 110, M = 26;
string s[N], sb[N];
int n, a[N], indeg[M];
bool g[M][M], fail = false;
int topo[M];
char ans[M+1];

void getTopo(){
    int len = 0;
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < M; ++j)
            if(g[i][j]) ++indeg[j];
    queue<int> q;
    for(int i = 0; i < M; ++i)
        if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int u = q.front();q.pop();
        topo[len++] = u;
        for(int v = 0; v < 26; ++v)
            if(g[u][v]){
                if(!--indeg[v]) q.push(v);
            }
    }
    if(len < 26) fail = true;
    for(int i = 0; i < 26; ++i)
        ans[topo[i]] = 'a' + i;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> s[i];
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) sb[i] = s[a[i]];
    for(int i = 1; i < n; ++i){
        int k = 0;
        while(k < sb[i].size() && k < sb[i+1].size() && sb[i][k]==sb[i+1][k]) ++k;
        if(k == sb[i].size()) continue;
        if(k == sb[i+1].size()){ fail = true; break; }
        g[sb[i][k]-'a'][sb[i+1][k]-'a'] = 1;
    }
    getTopo();
    if(fail) puts("NE");
    else puts("DA"), puts(ans);
    return 0;
}