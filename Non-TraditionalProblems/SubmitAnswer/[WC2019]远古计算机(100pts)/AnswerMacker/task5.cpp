#include<bits/stdc++.h>
using namespace std;

const int N=210;
struct MSG{int from,to,time;};
vector<int> g[N];
vector<MSG> msg[N];
bool bad[N][N],inq[N];
int dis[N],pre[N],n,m,ans=0;

bool operator < (const MSG &a,const MSG &b){return a.time<b.time;}

void spfa(int s,int t)
{
    memset(pre,0,sizeof(pre));
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;q.push(s);
    dis[s]=0;inq[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int v : g[u])
        {
            int w=dis[u]+1;
            while(bad[v][w]||bad[v][w+1]) w++;
            if(w<dis[v])
            {
                dis[v]=w;pre[v]=u;
                if(inq[v]) continue;
                inq[v]=1;q.push(v);
            }
        }
        q.pop();inq[u]=0;
    }
    for(int i=t,nxt=0;i;i=pre[i])
    {
        bad[i][dis[i]]=bad[i][dis[i]+1]=1;
        msg[i].push_back((MSG){pre[i],nxt,dis[i]});
        nxt=i;
    }
    ans=max(ans,dis[t]);
}

int main()
{

    freopen("oldcomputer5.in","r",stdin);
    freopen("oldcomputer5.out","w",stdout);
    int qwq;
    scanf("%d%d%d",&qwq,&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=10;i++) bad[i][0]=bad[i][1]=1;
    for(int i=1;i<=10;i++) spfa(i,101-i);
    for(int i=1;i<=n;i++)
    {
        if(msg[i].empty()) continue;
        sort(msg[i].begin(),msg[i].end());
        printf("node %d\n",i);
        for(MSG pp : msg[i])
        {
            printf("read %d a\n",pp.from);
            printf("write a %d\n",pp.to);
        }
    }
    cerr<<ans+2<<endl;
    return 0;
}
