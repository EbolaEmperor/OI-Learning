#include<bits/stdc++.h>
using namespace std;

const int N=60,M=10000;
int n,m,val[N],tot;
char s[3][N];
int dis[2][N][N];
int Hash[M],cnt;
int l[M],r[M],u[M],d[M];
int h[N],sum[N<<1],pos[M];
bool vis[N<<1];

void prework()
{
    cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            dis[0][i][j]=abs(s[0][i]-s[2][j])+val[abs(i-j)];
            dis[1][i][j]=abs(s[1][i]-s[2][j])+val[abs(i-j)];
            Hash[++cnt]=dis[0][i][j];
            Hash[++cnt]=dis[1][i][j];
        }
    sort(Hash+1,Hash+cnt+1);
    cnt=unique(Hash+1,Hash+1+cnt)-(Hash+1);
}

int valued()
{
    int res=0;
    for(int o=r[0];o;o=r[o]) vis[o]=0;
    for(int o=r[0];o;o=r[o])
    {
        if(vis[o]) continue;
        res++;vis[o]=1;
        for(int q=u[o];q!=o;q=u[q])
            for(int s=r[q];s!=q;s=r[s])
                vis[pos[s]]=1;
    }
    return res;
}

void add(int x)
{
    sum[pos[x]]++;
    for(int o=u[x];o!=x;o=u[o])
        r[l[o]]=o,l[r[o]]=o;
}

void del(int x)
{
    sum[pos[x]]--;
    for(int o=u[x];o!=x;o=u[o])
        r[l[o]]=r[o],l[r[o]]=l[o];
}

void link(int x,int p)
{
    pos[++tot]=p;sum[p]++;
    u[tot]=p;d[tot]=d[p];
    d[u[tot]]=tot;
    u[d[tot]]=tot;
    if(h[x]==-1) h[x]=l[tot]=r[tot]=tot;
    else
    {
        l[tot]=h[x];
        r[tot]=r[h[x]];
        r[l[tot]]=tot;
        l[r[tot]]=tot;
    }
}

bool dance(int dep)
{
    if(!r[0]) return 1;
    if(dep+valued()>m) return 0;
    int x=r[0];
    for(int o=r[0];o;o=r[o])
        if(sum[o]<sum[x]) x=o;
    for(int o=u[x];o!=x;o=u[o])
    {
        del(o);
        for(int q=r[o];q!=o;q=r[q]) del(q);
        if(dance(dep+1)) return 1;
        for(int q=r[o];q!=o;q=r[q]) add(q);
        add(o);
    }
    return 0;
}

void build(int x)
{
    tot=2*n;
    for(int i=0;i<=2*n;i++)
    {
        l[i]=i-1;r[i]=i+1;
        u[i]=d[i]=i;
        sum[i]=0;
        pos[i]=i;
    }
    l[0]=2*n;r[2*n]=0;
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(dis[0][i][j]<=x) link(j,i);
            if(dis[1][i][j]<=x) link(j,i+n);
        }
}

int main()
{
    int T;scanf("%d",&T);
    for(int cas=1;cas<=T;cas++)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) scanf("%d",val+i);
        for(int i=0;i<3;i++) scanf("%s",s[i]+1);
        prework();int l=0,r=cnt;
        while(l<=r)
        {
            int mid=(l+r)/2;
            build(Hash[mid]);
            if(dance(0)) r=mid-1;
            else l=mid+1;
        }
        printf("Case #%d: %d\n",cas,Hash[l]);
    }
    return 0;
}