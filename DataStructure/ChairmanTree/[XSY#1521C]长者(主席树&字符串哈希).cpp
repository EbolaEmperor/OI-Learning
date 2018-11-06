#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=100010;
int rt[N],lc[N*30],rc[N*30],tot=0;
ULL Hash[N*30],base[N];
char tops[N];
int n,m,ans[N];

void build(int &o,int l,int r)
{
    o=++tot;
    if(l==r){Hash[o]=tops[l];return;}
    int mid=(l+r)/2;
    build(lc[o],l,mid);
    build(rc[o],mid+1,r);
    Hash[o]=Hash[lc[o]]*base[r-mid]+Hash[rc[o]];
}

void insert(int &o,int p,int l,int r,int k,int x)
{
    o=++tot;lc[o]=lc[p];rc[o]=rc[p];
    if(l==r){Hash[o]=x;return;}
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],lc[o],l,mid,k,x);
    else insert(rc[o],rc[p],mid+1,r,k,x);
    Hash[o]=Hash[lc[o]]*base[r-mid]+Hash[rc[o]];
}

bool compare(int rt1,int rt2,int l,int r)
{
    if(l==r) return Hash[rt1]<Hash[rt2];
    int mid=(l+r)/2;
    if(Hash[lc[rt1]]==Hash[lc[rt2]])
        return compare(rc[rt1],rc[rt2],mid+1,r);
    return compare(lc[rt1],lc[rt2],l,mid);
}

inline bool cmp(const int &a,const int &b)
{
    if(Hash[rt[a]]==Hash[rt[b]]) return a<b;
    return compare(rt[a],rt[b],1,m);
}

int main()
{
    scanf("%d%d",&n,&m);
    base[0]=1;
    for(int i=1;i<=n;i++)
        base[i]=base[i-1]*233;
    scanf("%s",tops+1);
    build(rt[1],1,m);
    static char s[10];
    for(int i=2,p,pos;i<=n;i++)
    {
        scanf("%d%d%s",&p,&pos,s);
        insert(rt[i],rt[p],1,m,pos,s[0]);
    }
    for(int i=1;i<=n;i++) ans[i]=i;
    sort(ans+1,ans+1+n,cmp);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}