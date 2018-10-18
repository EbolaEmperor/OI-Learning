#include<bits/stdc++.h>
using namespace std;

const int N=60,P=5000;
const double eps=2e-7;
int l[P],r[P],u[P],d[P],tot;
int col[P],sum[N],h[N];
int pnt[N][2],crl[N][2];
int n,m,k,ans;
bool vis[N];

inline int sqr(const int &x){return x*x;}

void link(int x,int c)
{
    col[++tot]=c;sum[c]++;
    u[tot]=c;d[tot]=d[c];
    d[u[tot]]=u[d[tot]]=tot;
    if(h[x]!=-1)
    {
        l[tot]=h[x];r[tot]=r[h[x]];
        l[r[tot]]=r[l[tot]]=tot;
    }
    else h[x]=l[tot]=r[tot]=tot;
}

void build(double x)
{
    for(int i=0;i<=n;i++)
    {
        u[i]=d[i]=i;
        l[i]=i-1;r[i]=i+1;
        sum[i]=0;col[i]=i;
    }
    tot=l[0]=n;r[n]=0;
    memset(h,-1,sizeof(h));
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            int tmp=sqr(crl[i][0]-pnt[j][0]);
            tmp+=sqr(crl[i][1]-pnt[j][1]);
            if(tmp<=x*x) link(i,j);
        }
}

int valued()
{
    for(int o=r[0];o;o=r[o]) vis[o]=0;
    int res=0;
    for(int o=r[0];o;o=r[o])
    {
        if(vis[o]) continue;
        vis[o]=1;res++;
        for(int q=d[o];q!=o;q=d[q])
            for(int t=r[q];t!=q;t=r[t])
                vis[col[t]]=1;
    }
    return res;
}

void del(int x)
{
    sum[col[x]]--;
    for(int o=u[x];o!=x;o=u[o])
        l[r[o]]=l[o],r[l[o]]=r[o];
}

void add(int x)
{
    sum[col[x]]++;
    for(int o=d[x];o!=x;o=d[o])
        l[r[o]]=r[l[o]]=o;
}

void dance(int dep)
{
    if(!r[0]){ans=min(ans,dep);return;}
    if(dep+valued()>=ans) return;
    int x=r[0];
    for(int o=r[0];o;o=r[o])
        if(sum[o]<sum[x]) x=o;
    for(int o=d[x];o!=x;o=d[o])
    {
        del(o);
        for(int q=r[o];q!=o;q=r[q]) del(q);
        dance(dep+1);
        for(int q=l[o];q!=o;q=l[q]) add(q);
        add(o);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++) scanf("%d%d",pnt[i],pnt[i]+1);
        for(int i=1;i<=m;i++) scanf("%d%d",crl[i],crl[i]+1);
        double l=0,r=1000,mid;
        while(r-l>eps)
        {
            mid=(l+r)/2;
            build(mid);
            ans=m+1;dance(0);
            if(ans<=k) r=mid;
            else l=mid;
        }
        printf("%.6lf\n",l);
    }
    return 0;
}