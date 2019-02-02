#include<bits/stdc++.h>
using namespace std;

const int N=110;
vector<int> g[N];
bool inq[N];
int dis[N],pre[N],n,m;

void spfa()
{
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(1);dis[1]=0;
    while(!q.empty())
    {
        int u=q.front();
        for(int v : g[u])
            if(dis[u]+1<dis[v])
            {
                pre[v]=u;
                dis[v]=dis[u]+1;
                if(inq[v]) continue;
                inq[v]=1;q.push(v);
            }
        q.pop();inq[u]=0;
    }
    for(int i=n,nxt=0;i;i=pre[i])
    {
        printf("node %d\n",i);
        printf("read %d a\n",pre[i]);
        printf("write a %d\n",nxt);
        nxt=i;
    }
}

int main()
{
    freopen("oldcomputer3.in","r",stdin);
    freopen("oldcomputer3.out","w",stdout);
    int qwq;
    scanf("%d%d%d",&qwq,&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    spfa();
}