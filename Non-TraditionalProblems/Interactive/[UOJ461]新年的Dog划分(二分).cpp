#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

typedef pair<int,int> pii;
const int N=210;
vector<pii> baned,tree;
int unknow[N],n,tot;
bool done[N],single[N];
bool treg[N][N];
queue<int> q;

void reset_unkown()
{
    tot=0;
    for(int i=0;i<n;i++)
        if(!done[i]) unknow[++tot]=i;
}

bool check(int u,int r)
{
    vector<pii> ban=baned;
    for(int i=1;i<=r;i++)
        ban.emplace_back(pii(u,unknow[i]));
    return query(ban);
}

bool extend(int u,bool d)
{
    int l=1,r=tot,mid;
    if(check(u,tot)) return 0;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(u,mid)) l=mid+1;
        else r=mid-1; 
    }
    int v=unknow[l];
    single[v]=d^1;
    q.push(v);done[v]=1;
    tree.emplace_back(pii(u,v));
    treg[u][v]=treg[v][u]=1;
    reset_unkown();
}

bool bad()
{
    vector<pii> ban;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(single[i]!=single[j]&&!treg[i][j])
                ban.emplace_back(pii(i,j));
    for(pii e : tree)
    {
        ban.emplace_back(e);
        if(query(ban)) return 1;
        ban.pop_back();
    }
    return 0;
}

vector<int> check_bipartite(int vsize)
{
    n=vsize;q.push(0);
    done[0]=single[0]=1;
    reset_unkown();
    while(!q.empty()&&tot)
    {
        int u=q.front();q.pop();
        while(extend(u,single[u]));
        for(int i=1;i<=tot;i++)
            baned.emplace_back(pii(u,unknow[i]));
    }
    vector<int> res;
    if(bad()) return res;
    for(int i=0;i<n;i++)
        if(single[i]) res.emplace_back(i);
    return res;
}