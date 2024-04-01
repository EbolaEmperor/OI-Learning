#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int D = 210, N = 5010;
ull weight[D][N];
ull allfa[N];
int fa[D][N];
int d, n, m;
ull ans;
unordered_map<ull, int> mp;
vector<int> pset[D][N];

void change_allfa(int j, ull newallfa){
    ans -= mp[allfa[j]] * 2 - 1;
    mp[allfa[j]]--;
    allfa[j] = newallfa;
    mp[allfa[j]]++;
    ans += mp[allfa[j]] * 2 - 1;
}

void change_fa(int j, int id, int newfa){
    ull newallfa = allfa[j] ^ weight[id][fa[id][j]]
                            ^ weight[id][newfa];
    change_allfa(j, newallfa);
    fa[id][j] = newfa;
}

int main(){
    srand(19260817);
    scanf("%d%d%d", &d, &n, &m);
    for(int i = 1; i <= d; i++)
        for(int j = 1; j <= n; j++){
            weight[i][j] = (ull)rand()<<30|rand();
            fa[i][j] = j;
            pset[i][j].push_back(j);
            allfa[j] ^= weight[i][j];
        }
    for(int j = 1; j <= n; j++){
        mp[allfa[j]] = 1;
        ans++;
    }
    for(int i = 1; i <= m; i++){
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        a = fa[k][a];
        b = fa[k][b];
        if(a != b){
            if(pset[k][a].size() < pset[k][b].size()) swap(a, b);
            for(int p : pset[k][b]){
                change_fa(p, k, a);
                pset[k][a].push_back(p);
                fa[k][p] = a;
            }
            pset[k][b].clear();
        }
        printf("%llu\n", ans);
    }
    return 0;
}