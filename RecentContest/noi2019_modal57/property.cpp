#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=50010;
struct P{LL j;int v;} bad[N];
int p,n,m,s[N];
LL k;

struct Matrix
{
    int a[2][2];
    Matrix(){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator * (const Matrix &b)
    {
        Matrix c;
        for(int i=0;i<2;i++)
            for(int k=0;k<2;k++)
                for(int j=0;j<2;j++)
                    c.a[i][j]=(c.a[i][j]+1ll*a[i][k]*b.a[k][j])%p;
        return c;
    }
    friend Matrix operator ^ (Matrix a,LL b)
    {
        Matrix ans;
        ans[0][0]=ans[1][1]=1;
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
} mat[N<<2],E;

void build(int o,int l,int r)
{
    if(l==r)
    {
        mat[o][0][0]=s[l];
        mat[o][0][1]=s[l-1];
        mat[o][1][0]=1;
        return;
    }
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    mat[o]=mat[o<<1|1]*mat[o<<1];
}

Matrix query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mat[o];
    int mid=(l+r)/2;
    if(nr<=mid) return query(o<<1,l,mid,nl,nr);
    else if(nl>mid) return query(o<<1|1,mid+1,r,nl,nr);
    else return query(o<<1|1,mid+1,r,nl,nr)*query(o<<1,l,mid,nl,nr);
}

int main()
{
    E[0][0]=E[1][1]=1;
    scanf("%lld%d%d",&k,&p,&n);
    for(int i=0;i<n;i++)
        scanf("%d",s+i);
    s[n]=s[0];
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%lld%d",&bad[i].j,&bad[i].v);
    sort(bad+1,bad+1+m,[](P a,P b){return a.j<b.j;});
    while(bad[m].j>=k) m--;
    if(bad[m].j!=k-1) bad[++m]={k-1,s[(k-2)%n+1]};
    bad[m+1].j=k;
    LL pos=1,a=0,b=1;
    for(int i=1;i<=m;i++)
        if((pos-1)/n!=(bad[i].j-1)/n)
        {
            Matrix tmp=query(1,1,n,(pos-1)%n+1,n);
            LL ed=((pos-1)/n+1)*n+1;
            LL c=(bad[i].j-ed)/n;
            tmp=(mat[1]^c)*tmp;
            if((bad[i].j-2)/n==(bad[i].j-1)/n) tmp=query(1,1,n,1,(bad[i].j-2)%n+1)*tmp;
            Matrix cur;
            cur[0][0]=bad[i].v;
            cur[0][1]=(bad[i-1].j+1==bad[i].j)?bad[i-1].v:s[(bad[i].j-2)%n+1];
            cur[1][0]=1;
            tmp=cur*tmp;
            LL b1=(b*tmp[0][0]+a*tmp[0][1])%p;
            LL a1=(b*tmp[1][0]+a*tmp[1][1])%p;
            a=a1;b=b1;pos=bad[i].j+1;
            if(bad[i+1].j!=bad[i].j+1)
            {
                Matrix cur;
                cur[0][0]=s[bad[i].j%n+1];
                cur[0][1]=bad[i].v;
                cur[1][0]=1;
                LL b1=(b*cur[0][0]+a*cur[0][1])%p;
                LL a1=(b*cur[1][0]+a*cur[1][1])%p;
                a=a1;b=b1;pos++;
            }
        }
        else
        {
            Matrix tmp=(bad[i].j>pos)?query(1,1,n,(pos-1)%n+1,(bad[i].j-2)%n+1):E;
            Matrix cur;
            cur[0][0]=bad[i].v;
            cur[0][1]=(bad[i-1].j+1==bad[i].j)?bad[i-1].v:s[(bad[i].j-2)%n+1];
            cur[1][0]=1;
            tmp=cur*tmp;
            LL b1=(b*tmp[0][0]+a*tmp[0][1])%p;
            LL a1=(b*tmp[1][0]+a*tmp[1][1])%p;
            a=a1;b=b1;pos=bad[i].j+1;
            if(bad[i+1].j!=bad[i].j+1)
            {
                Matrix cur;
                cur[0][0]=s[bad[i].j%n+1];
                cur[0][1]=bad[i].v;
                cur[1][0]=1;
                LL b1=(b*cur[0][0]+a*cur[0][1])%p;
                LL a1=(b*cur[1][0]+a*cur[1][1])%p;
                a=a1;b=b1;pos++;
            }
        }
    cout<<b<<endl;
    return 0;
}