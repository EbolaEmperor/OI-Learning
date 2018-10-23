#include<bits/stdc++.h>
using namespace std;

const int N=100010,B=160;
int Hash[N],A[N],n,m;
bitset<N> cur,com[N/4+5];
struct Seg{int l,r,id;} seg[N*3];
int cnt[N],ans[N*3],tot=0;
bool done[N];

inline bool operator < (const Seg &a,const Seg &b)
{
    if(a.l/B!=b.l/B) return a.l<b.l;
    if((a.l/B)&1) return a.r>b.r;
    else return a.r<b.r;
}

void ins(int p){cnt[A[p]]++;cur[A[p]+cnt[A[p]]-1]=1;}
void del(int p){cur[A[p]+cnt[A[p]]-1]=0;cnt[A[p]]--;}

void solve(int m)
{
    tot=0;
    memset(cnt,0,sizeof(cnt));
    memset(done,0,sizeof(done));
    memset(ans,0,sizeof(ans));
    for(int i=1,l,r;i<=m;i++)
    {
        com[i].reset();
        scanf("%d%d",&l,&r);seg[++tot]={l,r,i};ans[i]+=r-l+1;
        scanf("%d%d",&l,&r);seg[++tot]={l,r,i};ans[i]+=r-l+1;
        scanf("%d%d",&l,&r);seg[++tot]={l,r,i};ans[i]+=r-l+1;
    }
    sort(seg+1,seg+1+tot);
    int pl=1,pr=0;cur.reset();
    for(int i=1;i<=tot;i++)
    {
        while(pl>seg[i].l) ins(--pl);
        while(pr<seg[i].r) ins(++pr);
        while(pl<seg[i].l) del(pl++);
        while(pr>seg[i].r) del(pr--);
        if(!done[seg[i].id]) com[seg[i].id]=cur,done[seg[i].id]=1;
        else com[seg[i].id]&=cur;
    }
    for(int i=1;i<=m;i++)
    {
        ans[i]-=3*com[i].count();
        printf("%d\n",ans[i]);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",A+i);
        Hash[i]=A[i];
    }
    sort(Hash+1,Hash+1+n);
    for(int i=1;i<=n;i++)
        A[i]=lower_bound(Hash+1,Hash+1+n,A[i])-Hash;
    while(m>=N/4) solve(N/4),m-=N/4;
    if(m) solve(m);
    return 0;
}