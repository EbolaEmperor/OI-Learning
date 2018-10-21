#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef pair<int,int> pii;
const int N=300010;
int col[N],mn[N],mx[N],n;
int tag[N<<2],val[N<<2];
pii stk[N];

void pushdown(int o,int l,int r)
{
    if(!tag[o]) return;
    int mid=(l+r)/2;
    val[o<<1]=mid-l+1;
    val[o<<1|1]=r-mid;
    tag[o<<1]=tag[o<<1|1]=1;
    tag[o]=0;
}

void modify(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr){val[o]=r-l+1;tag[o]=1;return;}
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nl<=mid) modify(o<<1,l,mid,nl,nr);
    if(nr>mid) modify(o<<1|1,mid+1,r,nl,nr);
    val[o]=val[o<<1]+val[o<<1|1];
}

int query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return val[o];
    int mid=(l+r)/2,res=0;pushdown(o,l,r);
    if(nl<=mid) res+=query(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=query(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int main()
{
    int T_T;scanf("%d",&T_T);
    while(T_T--)
    {
        scanf("%d",&n);
        memset(mn,0x7f,sizeof(int)*(n+3));
        memset(mx,0,sizeof(int)*(n+3));
        memset(tag,0,sizeof(int)*(n<<2));
        memset(val,0,sizeof(int)*(n<<2));
        for(int i=1;i<=n;i++)
        {
            scanf("%d",col+i);
            mn[col[i]]=min(mn[col[i]],i);
            mx[col[i]]=max(mx[col[i]],i);
        }
        long long ans=0;
        for(int i=1,top=0;i<=n;i++)
        {
            if(i==mx[col[i]]&&mn[col[i]]<mx[col[i]])
                modify(1,1,n,mn[col[i]]+1,mx[col[i]]);
            else stk[++top]=pii(col[i],i);
            while(top&&mx[stk[top].FR]<=i) top--;
            int l=top?stk[top].SE:0;
            if(l<i) ans+=i-l-query(1,1,n,l+1,i);
        }
        printf("%lld\n",ans);
    }
    return 0;
}