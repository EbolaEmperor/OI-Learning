#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

typedef long long LL;
typedef pair<LL,int> pli;
const int N=200010;
int n,tot=0,K;
LL must=0;
int A[N],Hash[N];
struct Type{int x,y,mid;} B[N];

pli operator + (const pli &a,const pli &b){return pli(a.FR+b.FR,a.SE+b.SE);}

struct Seg
{
    LL val[N<<2];int sz[N<<2];
    void build(int o,int l,int r)
    {
        val[o]=sz[o]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
    }
    void insert(int o,int l,int r,int k,int x)
    {
        val[o]+=x;sz[o]++;
        if(l==r) return;
        int mid=(l+r)/2;
        if(k<=mid) insert(o<<1,l,mid,k,x);
        else insert(o<<1|1,mid+1,r,k,x);
    }
    void remove(int o,int l,int r,int k,int x)
    {
        val[o]-=x;sz[o]--;
        if(l==r) return;
        int mid=(l+r)/2;
        if(k<=mid) remove(o<<1,l,mid,k,x);
        else remove(o<<1|1,mid+1,r,k,x);
    }
    pli query(int o,int l,int r,int nl,int nr)
    {
        if(nl>nr) return pli(0,0);
        if(l>=nl&&r<=nr) return pli(val[o],sz[o]);
        int mid=(l+r)/2;pli res(0,0);
        if(nl<=mid) res=res+query(o<<1,l,mid,nl,nr);
        if(nr>mid) res=res+query(o<<1|1,mid+1,r,nl,nr);
        return res;
    }
    int midnum(int o,int l,int r,int L=0,int R=0)
    {
        if(!sz[o]) return -1;
        if(l==r) return l;
        int mid=(l+r)/2,szl=sz[o<<1],szr=sz[o<<1|1];
        if(szl+L>=szr+R) return midnum(o<<1,l,mid,L,R+szr);
        else return midnum(o<<1|1,mid+1,r,szl+L,R);
    }
} t1,t2;

int work1()
{
    sort(A+1,A+1+tot);
    int pp=A[tot/2];LL res=0;
    for(int i=1;i<=tot;i++) res+=abs(pp-A[i]);
    printf("%lld\n",res+tot/2+must);
    return 0;
}

int work2()
{
    int fuck=0,m=0;
    for(int i=1;i<=tot;i+=2)
    {
        B[++m].mid=(A[i]+A[i+1])/2;
        B[m].x=Hash[++fuck]=A[i];
        B[m].y=Hash[++fuck]=A[i+1];
    }
    sort(Hash+1,Hash+1+fuck);
    int hs=unique(Hash+1,Hash+1+fuck)-(Hash+1);
    t1.build(1,1,hs);t2.build(1,1,hs);
    for(int i=1;i<=m;i++)
    {
        B[i].x=lower_bound(Hash+1,Hash+1+hs,B[i].x)-Hash;
        B[i].y=lower_bound(Hash+1,Hash+1+hs,B[i].y)-Hash;
        t2.insert(1,1,hs,B[i].x,Hash[B[i].x]);
        t2.insert(1,1,hs,B[i].y,Hash[B[i].y]);
    }
    sort(B+1,B+1+m,[](Type a,Type b){return a.mid<b.mid;});
    int pl=1;LL ans=INT64_MAX,tmp;
    for(int i=1;i<=m;i++)
    {
        t2.remove(1,1,hs,B[i].x,Hash[B[i].x]);
        t2.remove(1,1,hs,B[i].y,Hash[B[i].y]);
        t1.insert(1,1,hs,B[i].x,Hash[B[i].x]);
        t1.insert(1,1,hs,B[i].y,Hash[B[i].y]);
        int m1=t1.midnum(1,1,hs),m2=t2.midnum(1,1,hs);tmp=0;
        if(~m1)
        {
            pli p1=t1.query(1,1,hs,1,m1);
            pli p2=t1.query(1,1,hs,m1+1,hs);
            tmp+=1ll*Hash[m1]*p1.SE-p1.FR;
            tmp+=p2.FR-1ll*Hash[m1]*p2.SE;
        }
        if(~m2)
        {
            pli q1=t2.query(1,1,hs,1,m2);
            pli q2=t2.query(1,1,hs,m2+1,hs);
            tmp+=1ll*Hash[m2]*q1.SE-q1.FR;
            tmp+=q2.FR-1ll*Hash[m2]*q2.SE;
        }
        ans=min(ans,tmp);
    }
    printf("%lld\n",ans+m+must);
    return 0;
}

int main()
{
    int x,y;
    char s[5],t[5];
    scanf("%d%d",&K,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d%s%d",s,&x,t,&y);
        if(s[0]==t[0]) must+=abs(x-y);
        else A[++tot]=x,A[++tot]=y;
    }
    if(!tot) return printf("%lld\n",must),0;
    if(K==1) return work1();
    return work2();
}