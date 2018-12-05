#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353;
const int P=10000010;
const int N=300010;
int lc[P],rc[P],f[P],tag[P],tot;
int rt[N],n,m,Hash[N],ans;
int ch[N][2],cnt[N],p[N];

void pushdown(int o)
{
    if(!o||tag[o]==1) return;
    if(lc[o])
    {
        f[lc[o]]=(LL)f[lc[o]]*tag[o]%ha;
        tag[lc[o]]=(LL)tag[lc[o]]*tag[o]%ha;
    }
    if(rc[o])
    {
        f[rc[o]]=(LL)f[rc[o]]*tag[o]%ha;
        tag[rc[o]]=(LL)tag[rc[o]]*tag[o]%ha;
    }
    tag[o]=1;
}

void insert(int &o,int l,int r,int k)
{
    o=++tot;f[o]=tag[o]=1;
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],l,mid,k);
    else insert(rc[o],mid+1,r,k);
}

int merge(int p1,int p2,int l,int r,LL s1,LL s2,LL prob)
{
    pushdown(p1);pushdown(p2);
    if(!p1&&!p2) return 0;
    if(!p1)
    {
        f[p2]=(LL)f[p2]*(prob*s1%ha+(1-prob)*(1-s1)%ha)%ha;
        tag[p2]=(LL)tag[p2]*(prob*s1%ha+(1-prob)*(1-s1)%ha)%ha;
        return p2;
    }
    if(!p2)
    {
        f[p1]=(LL)f[p1]*(prob*s2%ha+(1-prob)*(1-s2)%ha)%ha;
        tag[p1]=(LL)tag[p1]*(prob*s2%ha+(1-prob)*(1-s2)%ha)%ha;
        return p1;
    }
    int o=++tot,mid=(l+r)/2;
    rc[o]=merge(rc[p1],rc[p2],mid+1,r,(s1+f[lc[p1]])%ha,(s2+f[lc[p2]]),prob);
    lc[o]=merge(lc[p1],lc[p2],l,mid,s1,s2,prob);
    f[o]=(f[lc[o]]+f[rc[o]])%ha;tag[o]=1;
    return o;
}

void getans(int o,int l,int r)
{
    if(l==r)
    {
        int sqr=(LL)f[o]*f[o]%ha;
        ans=(ans+(LL)l*Hash[l]%ha*sqr)%ha;
        return;
    }
    pushdown(o);
    int mid=(l+r)/2;
    getans(lc[o],l,mid);
    getans(rc[o],mid+1,r);
}

void dp(int u)
{
    if(!cnt[u]){insert(rt[u],1,m,p[u]);return;}
    for(int i=0;i<cnt[u];i++) dp(ch[u][i]);
    if(cnt[u]==1) rt[u]=rt[ch[u][0]];
    else rt[u]=merge(rt[ch[u][0]],rt[ch[u][1]],1,m,0,0,p[u]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1,fa;i<=n;i++)
    {
        scanf("%d",&fa);
        if(!fa) continue;
        ch[fa][cnt[fa]++]=i;
    }
    int inv=796898467;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",p+i);
        if(!cnt[i]) Hash[++m]=p[i];
        else p[i]=(LL)p[i]*inv%ha;
    }
    sort(Hash+1,Hash+1+m);
    m=unique(Hash+1,Hash+1+m)-(Hash+1);
    for(int i=1;i<=n;i++)
        if(!cnt[i]) p[i]=lower_bound(Hash+1,Hash+1+m,p[i])-Hash;
    dp(1);getans(rt[1],1,m);
    printf("%d\n",ans);
    return 0;
}