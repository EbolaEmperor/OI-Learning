#include<bits/stdc++.h>
using namespace std;

const int P=12010,N=2010;
int u[P],d[P],l[P],r[P],tot;
int h[N],sum[N],pos[P],row[P];
int n,m,ans[N],top=0;

void link(int x,int c)
{
    sum[c]++;
    pos[++tot]=c;row[tot]=x;
    u[tot]=c;d[tot]=d[c];
    u[d[tot]]=d[u[tot]]=tot;
    if(h[x]!=-1)
    {
        l[tot]=h[x];r[tot]=r[h[x]];
        l[r[tot]]=r[l[tot]]=tot;
    }
    else h[x]=l[tot]=r[tot]=tot;
}

void del(int c)
{
    l[r[c]]=l[c];r[l[c]]=r[c];
    for(int o=u[c];o!=c;o=u[o])
        for(int q=r[o];q!=o;q=r[q])
        {
            u[d[q]]=u[q];
            d[u[q]]=d[q];
            sum[pos[q]]--;
        }
}

void add(int c)
{
    for(int o=u[c];o!=c;o=u[o])
        for(int q=r[o];q!=o;q=r[q])
        {
            u[d[q]]=d[u[q]]=q;
            sum[pos[q]]++;
        }
    l[r[c]]=r[l[c]]=c;
}

bool dance()
{
    if(!r[0]) return 1;
    int x=r[0];
    for(int o=r[0];o;o=r[o])
        if(sum[o]<sum[x]) x=o;
    del(x);
    for(int o=u[x];o!=x;o=u[o])
    {
        for(int q=r[o];q!=o;q=r[q]) del(pos[q]);
        ans[++top]=row[o];
        if(dance()) return 1;
        ans[top--]=0;
        for(int q=r[o];q!=o;q=r[q]) add(pos[q]);
    }
    add(x);
    return 0;
}

int main()
{
    int x;
    scanf("%d%d",&n,&m);
    for(int i=0;i<=m;i++)
    {
        u[i]=d[i]=i;
        l[i]=i-1;r[i]=i+1;
        pos[i]=i;sum[i]=0;
    }
    l[0]=m;r[m]=0;tot=m;
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&x);
            if(x) link(i,j);
        }
    if(!dance()) puts("No Solution!");
    else for(int i=1;i<=top;i++) printf("%d ",ans[i]);
    return 0;
}