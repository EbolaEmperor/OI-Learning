#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*bH,*T;
    inline char Get()
    {
        if(bH==T) T=(bH=buf)+fread(buf,1,S,stdin);
        if(bH==T) return -1;return *bH++;
    }
    template<typename I>inline int read(I &x)
    {
        x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'a'||c>'z') c=Get();
        while(c>='a'&&c<='z') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using namespace IO;
typedef long long LL;
const int N=500010;
char s[N];
int sa[N],rk[N];
int height[N];
LL sum[N];
int w[19][N];
int n,m;

void getSA(int m)
{
    static int x[N],y[N],c[N],tmp[N];
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<m;i++) c[i+1]+=c[i];
    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
        for(int i=1;i<=n;i++) c[tmp[i]]++;
        for(int i=1;i<m;i++) c[i+1]+=c[i];
        for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
        num=1;swap(x,y);x[sa[1]]=1;
        for(int i=2;i<=n;i++)
            x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
        if(num==n) break;
        m=num;
    }
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
}

void getHeight()
{
    for(int i=1,k=0;i<=n;i++)
    {
        if(rk[i]==1) continue;
        if(k) k--;
        int j=sa[rk[i]-1];
        while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(n-sa[i]+1)-height[i];
    for(int i=1;i<=n;i++) w[0][i]=height[i];
    for(int i=1;i<=18;i++)
        for(int j=1;j<=n;j++)
            w[i][j]=min(w[i-1][j],w[i-1][j-(1<<i-1)]);
}

const int P=10000010;
int lc[P],rc[P],cnt[P];
int root[N],tot=0;

void Insert(int &o,int pre,int l,int r,int k)
{
    o=++tot;
    lc[o]=lc[pre];
    rc[o]=rc[pre];
    cnt[o]=cnt[pre]+1;
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) Insert(lc[o],lc[pre],l,mid,k);
    else Insert(rc[o],rc[pre],mid+1,r,k);
}

int Kth(int L,int R,int l,int r,int k)
{
    if(l==r) return l;
    int mid=(l+r)/2,szl=cnt[lc[R]]-cnt[lc[L]];
    if(k<=szl) return Kth(lc[L],lc[R],l,mid,k);
    else return Kth(rc[L],rc[R],mid+1,r,k-szl);
}

int Sum(int L,int R,int l,int r,int k)
{
    if(r<=k) return cnt[R]-cnt[L];
    int mid=(l+r)/2;
    int res=Sum(lc[L],lc[R],l,mid,k);
    if(k>mid) res+=Sum(rc[L],rc[R],mid+1,r,k);
    return res;
}

void Query1(LL k1,int k2)
{
    int L=lower_bound(sum+1,sum+1+n,k1)-sum;
    int len=k1-sum[L-1]+height[L],R=L;
    for(int i=18;i>=0;i--)
        if(R+(1<<i)<=n&&w[i][R+(1<<i)]>=len) R+=1<<i;
    int l=Kth(root[L-1],root[R],1,n,k2);
    print(l);putc(' ');print(l+len-1);putc('\n');
}

void Query2(int l,int r)
{
    int len=r-l+1,L=rk[l],R=L;
    for(int i=18;i>=0;i--)
        if(L-(1<<i)>=1&&w[i][L]>=len) L-=1<<i;
    for(int i=18;i>=0;i--)
        if(R+(1<<i)<=n&&w[i][R+(1<<i)]>=len) R+=1<<i;
    LL k1=sum[L-1]+(len-height[L]);
    int k2=Sum(root[L-1],root[R],1,n,l);
    print(k1);putc(' ');print(k2);putc('\n');
}

int main()
{
    int ty,y;LL x;
    reads(s);n=strlen(s+1);
    getSA(131);getHeight();
    for(int i=1;i<=n;i++)
        Insert(root[i],root[i-1],1,n,sa[i]);
    for(read(m);m;m--)
    {
        read(ty);read(x);read(y);
        if(ty==1) Query1(x,y);
        else Query2(x,y);
    }
    flush();
    return 0;
}