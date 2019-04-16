#include<bits/stdc++.h>
using namespace std;

const int N=100010,ha=998244353;
int mul[N<<2],fmul[N<<2],fadd[N<<2],f[N<<2],val[N<<2];
int n,m,t,pw2[N];
int ans1,ans2;

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}
inline void mns(int &x,const int &y){x=(x-y<0)?(x-y+ha):(x-y);}

inline void pushmul(int o,int k){val[o]=1ll*val[o]*k%ha;mul[o]=1ll*mul[o]*k%ha;}
inline void pushfmul(int o,int k){f[o]=1ll*f[o]*k%ha;fmul[o]=1ll*fmul[o]*k%ha;fadd[o]=1ll*fadd[o]*k%ha;}
inline void pushfadd(int o,int k){add(f[o],k);add(fadd[o],k);}
void pushdown(int o)
{
    if(mul[o]>1) pushmul(o<<1,mul[o]),pushmul(o<<1|1,mul[o]),mul[o]=1;
    if(fmul[o]>1) pushfmul(o<<1,fmul[o]),pushfmul(o<<1|1,fmul[o]),fmul[o]=1;
    if(fadd[o]) pushfadd(o<<1,fadd[o]),pushfadd(o<<1|1,fadd[o]),fadd[o]=0;
}

void build(int o,int l,int r)
{
    fmul[o]=mul[o]=1;
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void update(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr)
    {
        mns(ans1,val[o]);
        add(val[o],pw2[t]);
        add(mul[o],mul[o]);
        pushfadd(o,pw2[t]);
        add(ans2,val[o]);
        return;
    }
    if(r<nl||l>nr)
    {
        mns(ans1,val[o]);
        add(val[o],f[o]);
        pushfmul(o,2);
        add(mul[o],mul[o]);
        add(ans2,val[o]);
        return;
    }
    int mid=(l+r)/2;pushdown(o);
    mns(ans1,val[o]);add(ans2,val[o]);
    update(o<<1,l,mid,nl,nr);
    update(o<<1|1,mid+1,r,nl,nr);
}

int main()
{
    scanf("%d%d",&n,&m);
    build(1,1,n);
    pw2[0]=1;
    for(int i=1;i<=m;i++)
        add(pw2[i]=pw2[i-1],pw2[i-1]);
    int opt,l,r;
    while(m--)
    {
        scanf("%d",&opt);
        if(opt==1)
        {
            ans2=0;
            scanf("%d%d",&l,&r);
            update(1,1,n,l,r);
            ans1=(2ll*ans1+ans2)%ha;
            t++;
        }
        else printf("%d\n",ans1);
    }
    return 0;
}
