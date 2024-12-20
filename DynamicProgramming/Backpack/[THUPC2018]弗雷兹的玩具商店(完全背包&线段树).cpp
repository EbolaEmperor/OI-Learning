#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010,M=65;
int n,m,c[N],v[N],val[M];
int mxv[N<<2][M],tagc[N<<2],tagv[N<<2];
LL f[M];

void maintain(int o){for(int i=1;i<=m;i++) mxv[o][i]=max(mxv[o<<1][i],mxv[o<<1|1][i]);}
void pushc(int o,int d)
{
    static int tmp[M];
    for(int i=1;i<=m-d;i++) tmp[i+d]=mxv[o][i];
    for(int i=m-d+1;i<=m;i++) tmp[i+d-m]=mxv[o][i];
    memcpy(mxv[o],tmp,sizeof(tmp));(tagc[o]+=d)%=m;
}
void pushv(int o,int d){for(int i=1;i<=m;i++) mxv[o][i]+=d;tagv[o]+=d;}
void pushdown(int o)
{
    if(tagc[o]) pushc(o<<1,tagc[o]),pushc(o<<1|1,tagc[o]),tagc[o]=0;
    if(tagv[o]) pushv(o<<1,tagv[o]),pushv(o<<1|1,tagv[o]),tagv[o]=0;
}
void build(int o,int l,int r)
{
    tagc[o]=tagv[o]=0;
    memset(mxv[o],-0x3f,sizeof(mxv[o]));
    if(l==r){mxv[o][c[l]]=v[l];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}
void updatec(int o,int l,int r,int nl,int nr,int d)
{
    if(l>=nl&&r<=nr){pushc(o,d);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) updatec(o<<1,l,mid,nl,nr,d);
    if(nr>mid) updatec(o<<1|1,mid+1,r,nl,nr,d);
    maintain(o);
}
void updatev(int o,int l,int r,int nl,int nr,int d)
{
    if(l>=nl&&r<=nr){pushv(o,d);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) updatev(o<<1,l,mid,nl,nr,d);
    if(nr>mid) updatev(o<<1|1,mid+1,r,nl,nr,d);
    maintain(o);
}
void getval(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr)
    {
        for(int i=1;i<=m;i++)
            val[i]=max(val[i],mxv[o][i]);
        return;
    }
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) getval(o<<1,l,mid,nl,nr);
    if(nr>mid) getval(o<<1|1,mid+1,r,nl,nr);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<=n;i++) scanf("%d",v+i);
    build(1,1,n);
    int q,opt,l,r,x;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1) scanf("%d",&x),updatec(1,1,n,l,r,x);
        if(opt==2) scanf("%d",&x),updatev(1,1,n,l,r,x);
        if(opt==3)
        {
            memset(val,0,sizeof(val));
            memset(f,0,sizeof(f));
            getval(1,1,n,l,r);
            for(int i=1;i<=m;i++)
                for(int j=0;j<=m-i;j++)
                    f[i+j]=max(f[i+j],f[j]+val[i]);
            LL A=0,B=0;
            for(int i=1;i<=m;i++)
                A+=f[i],B^=f[i];
            printf("%lld %lld\n",A,B);
        }
    }
    return 0;
}