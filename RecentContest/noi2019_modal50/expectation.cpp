#include<bits/stdc++.h>
using namespace std;

typedef long double LD;
const int N=200010;
struct Edge{int u,v,w,c;} e[N],cur[35];
LD mat[35][35],g[35][35];
int fa[N],ffa[N],n,m;
LD ans=0;

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int ffind(int x){return ffa[x]==x?x:ffa[x]=ffind(ffa[x]);}

LD gauss(int n)
{
    LD res=1;
    for(int i=1;i<n;i++)
    {
        int p=i;
        while(p<n&&fabs(mat[p][i])<1e-6) p++;
        if(p>=n) return 0;
        if(p!=i)
        {
            for(int j=1;j<n;j++)
                swap(mat[p][j],mat[i][j]);
            res=-res;
        }
        res*=mat[i][i];
        for(int j=i+1;j<n;j++)
        {
            LD t=mat[j][i]/mat[i][i];
            for(int k=i;k<n;k++)
                mat[j][k]-=t*mat[i][k];
        }
    }
    return res;
}

void gao(int m)
{
    static int idx[N],vtx[65];
    int tot=0;
    memset(mat,0,sizeof(mat));
    for(int i=1;i<=m;i++)
    {
        int u=cur[i].u,v=cur[i].v;
        u=find(u);v=find(v);
        if(!idx[u]) vtx[idx[u]=++tot]=u;
        if(!idx[v]) vtx[idx[v]=++tot]=v;
        cur[i].u=idx[u];
        cur[i].v=idx[v];
    }
    for(int i=1;i<=tot;i++) ffa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int u=cur[i].u,v=cur[i].v;
        u=ffind(u);v=ffind(v);
        if(u!=v) ffa[u]=v;
    }
    for(int i=1;i<=tot;i++)
    {
        if(ffa[i]!=i) continue;
        static int ind[65],vx[35];
        int sum=0;
        for(int j=1;j<=tot;j++)
            if(ffind(j)==i) vx[ind[j]=++sum]=j;
        memset(g,0,sizeof(g));
        for(int j=1;j<=m;j++)
        {
            if(ffind(cur[j].u)!=i) continue;
            int u=ind[cur[j].u],v=ind[cur[j].v];
            g[u][u]++;g[v][v]++;
            g[u][v]--;g[v][u]--;
        }
        memcpy(mat,g,sizeof(mat));
        LD res=gauss(sum);
        for(int j=1;j<=m;j++)
        {
            if(ffind(cur[j].u)!=i) continue;
            int u=ind[cur[j].u],v=ind[cur[j].v];
            memcpy(mat,g,sizeof(mat));
            mat[u][u]--;mat[v][v]--;
            mat[u][v]++;mat[v][u]++;
            ans+=(LD)cur[j].c*(res-gauss(sum))/res;
        }
    }
    for(int i=1;i<=tot;i++) idx[vtx[i]]=0;
}

void kruskal()
{
    sort(e+1,e+1+m,[](Edge a,Edge b){return a.w<b.w;});
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,cnt=0;i<=m;i++)
    {
        cur[++cnt]=e[i];
        if(e[i+1].w==e[i].w) continue;
        gao(cnt);
        for(int j=i;j>i-cnt;j--)
        {
            int u=e[j].u,v=e[j].v;
            u=find(u);v=find(v);
            if(u!=v) fa[u]=v;
        }
        cnt=0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].w,&e[i].c);
    kruskal();
    printf("%.5Lf\n",ans);
    return 0;
}