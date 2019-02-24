#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=1010;
vector<int> g[N];
vector<pii> msg[N];
int dis[N],n,m;
bool inq[N];

void spfa()
{
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    for(int i=51;i<=100;i++)
    {
        dis[i]=0;
        inq[i]=1;
        q.push(i);
    }
    while(!q.empty())
    {
        int u=q.front();
        for(int v : g[u])
            if(dis[u]+1<dis[v])
            {
                dis[v]=dis[u]+1;
                if(inq[v]) continue;
                inq[v]=1;q.push(v);
            }
        q.pop();inq[u]=0;
    }
}

int main()
{
    freopen("oldcomputer4.in","r",stdin);
    freopen("oldcomputer4.out","w",stdout);
    int qwq;
    scanf("%d%d%d",&qwq,&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    spfa();
    queue<int> q;
    for(int i=1;i<=50;i++)
    {
        q.push(i);
        msg[i].push_back(pii(0,0));
    }
    while(!q.empty())
    {
        int u=q.front(),v=0;q.pop();
        for(int vv : g[u]) if(dis[u]==dis[vv]+1) v=vv;
        printf("node %d\n",u);
        sort(msg[u].begin(),msg[u].end());
        for(pii pr : msg[u])
        {
            printf("read %d a\n",pr.second);
            printf("write a %d\n",v);
            msg[v].push_back(pii(pr.first+1,u));
        }
        if(v) q.push(v);
    }
    return 0;
}
