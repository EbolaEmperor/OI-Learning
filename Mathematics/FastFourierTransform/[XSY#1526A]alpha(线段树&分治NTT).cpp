#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
int mmp[27000000],*pos=mmp;
int* newint(int x){int* p=pos;pos+=x;return p;}

typedef long long LL;
const int ha=998244353;
const int N=100010;
struct OPT{int l,r,p;} opt[N];
int A[N<<2],B[N<<2],r[N<<2];
vector<int> tr[N<<2];
int len[N<<2],sum=0;
int* poly[N<<2];
int Hash[N],hs;
int n,k,ans=0;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

inline int add(const int &x,const int &y){return x+y>=ha?x+y-ha:x+y;}
inline int dev(const int &x,const int &y){return x-y<0?x-y+ha:x-y;}

void NTT(int *A,int n,int d)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int p=i<<1,wn=Pow((d==1)?3:332748118,(ha-1)/p);
        for(int j=0;j<n;j+=p)
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=(LL)w*A[i+j+k]%ha;
                A[j+k]=add(x,y);
                A[i+j+k]=dev(x,y);
                w=(LL)w*wn%ha;
            }
    }
    int inv=(d==-1)?Pow(n,ha-2):0;
    if(d==-1) for(int i=0;i<n;i++) A[i]=(LL)A[i]*inv%ha;
}

void multi(int *res,int *a,int *b,int n,int m)
{
    if(n<=80||m<=80)
    {
        memset(A,0,sizeof(int)*(n+m+1));
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                A[i+j]=(A[i+j]+(LL)a[i]*b[j])%ha;
        memcpy(res,A,sizeof(int)*min(n+m+1,k+1));
        return;
    }
    int len=1,l=0;for(;len<=n+m;len<<=1,l++);
    for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
    for(int i=0;i<len;i++) A[i]=(i<=n)?a[i]:0;
    for(int i=0;i<len;i++) B[i]=(i<=m)?b[i]:0;
    NTT(A,len,1);NTT(B,len,1);
    for(int i=0;i<len;i++)
        A[i]=(LL)A[i]*B[i]%ha;
    NTT(A,len,-1);
    memcpy(res,A,sizeof(int)*min(n+m+1,k+1));
}

int* divide(int l,int r,int x)
{
    if(l==r)
    {
        int* res=newint(2);
        res[0]=ha+1-tr[x][l];
        res[1]=tr[x][l];
        return res;
    }
    int mid=(l+r)/2;
    int* L=divide(l,mid,x);
    int* R=divide(mid+1,r,x);
    int* res=newint(min(r-l+2,k+1));
    multi(res,L,R,min(mid-l+1,k),min(r-mid,k));
    return res;
}

void addpoly(int o,int l,int r,int nl,int nr,int p)
{
    if(l>=nl&&r<=nr)
    {
        tr[o].push_back(p);
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) addpoly(o<<1,l,mid,nl,nr,p);
    if(nr>mid) addpoly(o<<1|1,mid+1,r,nl,nr,p);
}

void gao(int o,int l,int r)
{
    len[o]=min(k,(int)tr[o].size());
    poly[o]=newint(len[o]+1);poly[o][0]=1;
    if(tr[o].size()) poly[o]=divide(0,tr[o].size()-1,o);
    if(l==r)
    {
        int leng=Hash[l+1]-Hash[l];
        for(int i=0;i<=len[o];i++)
            poly[o][i]=(LL)poly[o][i]*leng%ha;
        return;
    }
    int mid=(l+r)/2;
    gao(o<<1,l,mid);
    gao(o<<1|1,mid+1,r);
    if(len[o<<1]<len[o<<1|1])
    {
        swap(len[o<<1],len[o<<1|1]);
        swap(poly[o<<1],poly[o<<1|1]);
    }
    for(int i=0;i<=len[o<<1|1];i++)
        poly[o<<1][i]=add(poly[o<<1][i],poly[o<<1|1][i]);
    int *g=newint(min(len[o]+len[o<<1],k)+1);
    multi(g,poly[o],poly[o<<1],len[o],len[o<<1]);
    poly[o]=g;len[o]=min(len[o]+len[o<<1],k);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        opt[i].l=read();
        opt[i].r=read();
        opt[i].p=read();
        Hash[++hs]=opt[i].l;
        Hash[++hs]=opt[i].r+1;
    }
    k=read();
    sort(Hash+1,Hash+1+hs);
    hs=unique(Hash+1,Hash+1+hs)-(Hash+1);
    for(int i=1;i<=n;i++)
    {
        int l=lower_bound(Hash+1,Hash+1+hs,opt[i].l)-Hash;
        int r=lower_bound(Hash+1,Hash+1+hs,opt[i].r+1)-Hash-1;
        addpoly(1,1,hs-1,l,r,opt[i].p);
    }
    gao(1,1,hs-1);
    printf("%d\n",poly[1][k]);
    return 0;
}