#include<bits/stdc++.h>
using namespace std;

const int N=5010;
vector<int> g[N];
int n,p,t,val[N],a[N];
double ans=0,f[N][3],cur;
// f[u][0/1/2]: 节点u，不选/选一条不封顶链/选一条封顶链  

void dfs(int u,int fa)
{
    double mx1=-1e18,mx2=-1e18,all=0;
    for(int v : g[u])
    {
        if(v==fa) continue;
        dfs(v,u);
        all+=max(f[v][0],f[v][2]);
        double tmp=f[v][1]-max(f[v][0],f[v][2]);
        if(tmp>mx1) mx2=mx1,mx1=tmp;
        else if(tmp>mx2) mx2=tmp;
    }
    f[u][0]=all;
    f[u][1]=max(all+mx1+a[u],all+a[u]);
    f[u][2]=max(all+mx1+mx2+a[u]-cur,f[u][1]-cur);
}

bool check(double x)
{
    memset(f,0,sizeof(f));
    cur=x;dfs(1,0);
    return max(f[1][0],f[1][2])>x;
}

void gao()
{
    double l=ans,r=0,mid;
    for(int i=1;i<=n;i++) r+=a[i];
    while(r-l>5e-7)
    {
        mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    ans=r;
}

int main()
{
    srand(19260817);
    scanf("%d%d",&n,&p);
    for(int i=1;i<=n;i++)
        scanf("%d",val+i);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf("%d",&t);
    static int add[N],tot=0;
    for(int i=1;i<=n;i++)
        add[++tot]=min(t,p-1-val[i]);
    sort(add+1,add+tot+1);
    tot=unique(add+1,add+tot+1)-(add+1);
    random_shuffle(add+1,add+tot+1);
    for(int i=1;i<=tot;i++)
    {
        int c=add[i];
        for(int j=1;j<=n;j++)
            a[j]=(val[j]+c)%p;
        if(check(ans)) gao();
    }
    printf("%.7lf\n",ans);
    return 0;
}
