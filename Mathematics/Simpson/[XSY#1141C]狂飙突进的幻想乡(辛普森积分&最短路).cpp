#include<bits/stdc++.h>
#define double long double
using namespace std;
 
const int N=210;
const double eps=1e-6;
struct Edge{int to,next;double capa;} e[N<<2];
double capx[N<<2],capy[N<<2];
int h[N],sum=0,n,m,s,t;
double dis[N];
bool vis[N];
 
void add_edge(int u,int v,double wx,double wy)
{
    e[++sum].to=v;
    capx[sum]=wx;
    capy[sum]=wy;
    e[sum].next=h[u];
    h[u]=sum;
}
 
double SPFA(double a)
{
    for(int i=1;i<=sum;i++)
        e[i].capa=a*capx[i]+(1-a)*capy[i];
    for(int i=1;i<=n;i++) dis[i]=1e20;
    memset(vis,0,sizeof(vis));
    queue<int> q;q.push(s);
    dis[s]=0;vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int tmp=h[u];tmp;tmp=e[tmp].next)
        {
            int v=e[tmp].to;
            if(dis[v]>dis[u]+e[tmp].capa)
            {
                dis[v]=dis[u]+e[tmp].capa;
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
        q.pop();vis[u]=0;
    }
    return dis[t];
}
 
double calc(double l,double r)
{
    double mid=(l+r)/2;
    return (r-l)*(SPFA(l)+4*SPFA(mid)+SPFA(r))/6;
}
double Simpson(double l,double r,double A)
{
    double mid=(l+r)/2;
    double L=calc(l,mid),R=calc(mid,r);
    return fabs(L+R-A)<eps?L+R:Simpson(l,mid,L)+Simpson(mid,r,R);
}
 
int main()
{
    int u,v;double x,y;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%Lf%Lf",&u,&v,&x,&y);
        add_edge(u,v,x,y);
        add_edge(v,u,x,y);
    }
    printf("%.4Lf\n",Simpson(0,1,calc(0,1)));
    return 0;
}