#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=500010;
vector<int> G[N],vG[N];
multiset<int> cur;
int n,m,in[N],out[N];
int pre[N],suf[N];
int topo[N],cnt=0;

void prework()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();topo[++cnt]=u;q.pop();
        for(int v : G[u])
        {
            pre[v]=max(pre[v],pre[u]+1);
            if(!--in[v]) q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(!out[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int v : vG[u])
        {
            suf[v]=max(suf[v],suf[u]+1);
            if(!--out[v]) q.push(v);
        }
    }
}

void xi_jin_ping_is_good()
{
    int node,ans=n+1;
    for(int i=1;i<=n;i++) cur.insert(suf[i]);
    for(int i=1;i<=n;i++)
    {
        int u=topo[i];
        cur.erase(cur.find(suf[u]));
        for(int v : vG[u]) cur.erase(cur.find(pre[v]+suf[u]+1));
        auto maxdis=cur.end();maxdis--;
        if(*maxdis<ans) ans=*maxdis,node=u;
        for(int v : G[u]) cur.insert(pre[u]+suf[v]+1);
        cur.insert(pre[u]);
    }
    printf("%d %d\n",node,ans);
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        G[u].push_back(v);
        vG[v].push_back(u);
        in[v]++;out[u]++;
    }
    prework();
    xi_jin_ping_is_good();
    return 0;
}