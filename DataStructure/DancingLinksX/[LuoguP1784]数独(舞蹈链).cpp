#include<bits/stdc++.h>
using namespace std;

const int N=740,M=340,P=10000;
int u[P],d[P],l[P],r[P],tot;
int row[P],col[P],sum[M],h[N];
int ans[M],top=0;

void link(int x,int c)
{
    sum[c]++;
    col[++tot]=c;row[tot]=x;
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
    for(int o=d[c];o!=c;o=d[o])
        for(int q=r[o];q!=o;q=r[q])
        {
            u[d[q]]=u[q];
            d[u[q]]=d[q];
            sum[col[q]]--;
        }
}

void add(int c)
{
    for(int o=u[c];o!=c;o=u[o])
        for(int q=l[o];q!=o;q=l[q])
        {
            u[d[q]]=d[u[q]]=q;
            sum[col[q]]++;
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
        for(int q=r[o];q!=o;q=r[q]) del(col[q]);
        ans[++top]=row[o];
        if(dance()) return 1;
        ans[top--]=0;
        for(int q=l[o];q!=o;q=l[q]) add(col[q]);
    }
    add(x);
    return 0;
}

void ins(int i,int j,int x)
{
    link(9*(i*9+j)+x,i*9+j+1);
    link(9*(i*9+j)+x,i*9+x+81);
    link(9*(i*9+j)+x,j*9+x+162);
    link(9*(i*9+j)+x,(i/3*3+j/3)*9+x+243);
}

int main()
{
    int x;tot=81*4;
    for(int i=0;i<=tot;i++)
    {
        r[i]=i+1;l[i]=i-1;
        u[i]=d[i]=i;
        col[i]=i;
    }
    l[0]=tot;r[tot]=0;
    memset(h,-1,sizeof(h));
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            scanf("%d",&x);
            if(x){ins(i,j,x);continue;}
            for(int k=1;k<=9;k++) ins(i,j,k);
        }
    dance();int cnt=0;
    sort(ans+1,ans+1+top);
    for(int i=0;i<9;i++,puts(""))
        for(int j=0;j<9;j++)
            printf("%d ",(ans[++cnt]-1)%9+1);
    return 0;
}