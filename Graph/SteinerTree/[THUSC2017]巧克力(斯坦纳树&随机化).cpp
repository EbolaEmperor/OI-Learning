#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=250;
vector<int> g[N];
int a[N],c[N],n,m,k;
int val[N],stu[N],col[N];
int f[32][N];
bool inq[N];

inline int idx(const int &x,const int &y){return (x-1)*m+y;}
void add(int u,int v){g[u].push_back(v);g[v].push_back(u);}

void spfa(int *dis)
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(c[i]>=0) q.push(i),inq[i]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int v : g[u])
        {
            if(c[v]<0) continue;
            if(dis[u]+val[v]<dis[v])
            {
                dis[v]=dis[u]+val[v];
                if(inq[v]) continue;
                q.push(v);inq[v]=1;
            }
        }
        q.pop();inq[u]=0;
    }
}

int calc(int x)
{
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        f[0][i]=0;
        val[i]=(a[i]>x)?1001:999;
        if(c[i]<0) continue;
        f[col[i]][i]=val[i];
    }
    for(int s=0;s<1<<k;s++)
    {
        for(int t=(s-1)&s;t;t=(t-1)&s)for(int u=1;u<=n;u++)
            if(c[u]>=0) f[s][u]=min(f[s][u],f[t][u]+f[s^t][u]-val[u]);
        spfa(f[s]);
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,f[(1<<k)-1][i]);
    return ans;
}

pii gao()
{
    for(int i=0;i<=n;i++) stu[i]=rand()%k;
    for(int i=1;i<=n;i++) if(c[i]>=0) col[i]=1<<stu[c[i]];
    int cnt=(calc(1e6)+n)/1000;
    int l=0,r=1e6,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        int tmp=calc(mid)%1000;
        if(tmp>n||tmp==0) r=mid-1;
        else l=mid+1;
    }
    return pii(cnt,l);
}

int main()
{
    srand(time(0));
    int ToT;scanf("%d",&ToT);
    while(ToT--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",c+idx(i,j));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",a+idx(i,j));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(i<n) add(idx(i,j),idx(i+1,j));
                if(j<m) add(idx(i,j),idx(i,j+1));
            }
        pii ans=gao();n*=m;
        for(int t=1;t<=200;t++) ans=min(ans,gao());
        printf("%d %d\n",ans.first,ans.second);
        for(int i=1;i<=n;i++) g[i].clear();
    }
    return 0;
}