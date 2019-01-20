#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=100010;
int minv[N<<2],tmn[N<<2],sum[N<<2];
int n,p[N],f[N];

inline int add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

inline void maintain(int o)
{
    minv[o]=min(minv[o<<1],minv[o<<1|1]);sum[o]=0;
    if(minv[o]==minv[o<<1]) add(sum[o],sum[o<<1]);
    if(minv[o]==minv[o<<1|1]) add(sum[o],sum[o<<1|1]);
}

inline void upmin(int o,int x){minv[o]+=x;tmn[o]+=x;}

inline void pushdown(int o)
{
    if(!tmn[o]) return;
    upmin(o<<1,tmn[o]);
    upmin(o<<1|1,tmn[o]);
    tmn[o]=0;
}

void build(int o,int l,int r)
{
    minv[o]=l;sum[o]=0;
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void addmn(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr){upmin(o,x);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) addmn(o<<1,l,mid,nl,nr,x);
    if(nr>mid) addmn(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

void update(int o,int l,int r,int k,int x)
{
	if(l==r){sum[o]=x;return;}
	int mid=(l+r)/2;pushdown(o);
	if(k<=mid) update(o<<1,l,mid,k,x);
	else update(o<<1|1,mid+1,r,k,x);
	maintain(o);
}

int query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return minv[o]?0:sum[o];
    int mid=(l+r)/2,res=0;pushdown(o);
    if(nl<=mid) add(res,query(o<<1,l,mid,nl,nr));
    if(nr>mid) add(res,query(o<<1|1,mid+1,r,nl,nr));
    return res;
}

void falun_dafa_is_good()
{
    static int stk1[N],stk2[N],top1=0,top2=0;
    f[0]=1;
    for(int i=1;i<=n;i++)
    {
        while(top1&&p[i]>p[stk1[top1]])
            addmn(1,1,n,stk1[top1-1]+1,stk1[top1],p[i]-p[stk1[top1]]),top1--;
        stk1[++top1]=i;
        while(top2&&p[i]<p[stk2[top2]])
            addmn(1,1,n,stk2[top2-1]+1,stk2[top2],p[stk2[top2]]-p[i]),top2--;
        stk2[++top2]=i;
        upmin(1,-1);
        update(1,1,n,i,f[i-1]);
        f[i]=query(1,1,n,1,i);
    }
    printf("%d\n",f[n]);
}

int main()
{
    scanf("%d",&n);build(1,1,n);
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    falun_dafa_is_good();
    return 0;
}