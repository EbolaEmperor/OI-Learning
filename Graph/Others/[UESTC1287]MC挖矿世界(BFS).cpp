#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 2005;
set<int> S;
string s[maxn];
vector<int> g[maxn];
long long ans = 0;
int n,d[maxn];
queue<int> Q;

void solve(int x)
{
    S.clear();while(!Q.empty())Q.pop();
    for(int i=0;i<n;i++)if(i!=x)S.insert(i);
    for(int i=0;i<n;i++)d[i]=n;
    d[x]=0,Q.push(x);
    while(!Q.empty())
    {
        int u = Q.front();Q.pop();
        if(S.size() < g[u].size()){
            set<int>::iterator it=S.begin();
            while(S.size()&&it!=S.end())
            {
                int v = *it;
                auto jt = it;
                if(s[u][v] == '1')
                {
                    d[v]=d[u]+1;
                    it++;
                    S.erase(jt);
                    Q.push(v);
                }
                else it++;
            }
        } else {
            for(int v : g[u]){
                if(d[v] < n) continue;
                d[v] = d[u] + 1;
                Q.push(v);
                S.erase(v);
            }
        }
    }
    for(int i=0;i<n;i++)
        ans+=d[i]*d[i];
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(int j = 0; j < n; j++)
            if(s[i][j] == '1') g[i].push_back(j);
    }
    for(int i=0;i<n;i++)solve(i);
    cout<<ans<<endl;
}