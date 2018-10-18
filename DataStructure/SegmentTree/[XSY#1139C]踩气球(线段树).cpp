#include<bits/stdc++.h>
using namespace std;

namespace IO
{
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
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
        putc('\n');
	}
}

using namespace IO;
const int N=100010;
int a[N],n,m,ans=0;
int sum[N<<2];
int rest[N];
vector<int> seg[N<<2];

void Build(int o,int l,int r)
{
    if(l==r)
    {
        sum[o]=a[l];
        return;
    }
    int mid=(l+r)/2;
    Build(o<<1,l,mid);
    Build(o<<1|1,mid+1,r);
    sum[o]=sum[o<<1]+sum[o<<1|1];
}

void Insert(int o,int l,int r,int nl,int nr,int k)
{
    if(l>=nl&&r<=nr)
    {
        seg[o].push_back(k);
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) Insert(o<<1,l,mid,nl,nr,k);
    if(nr>mid) Insert(o<<1|1,mid+1,r,nl,nr,k);
}

void gao(int o,int len)
{
    for(auto it : seg[o])
        if(!(rest[it]-=len)) ans++;
}

void Delete(int o,int l,int r,int k)
{
    if(!--sum[o]) gao(o,r-l+1);
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) Delete(o<<1,l,mid,k);
    else Delete(o<<1|1,mid+1,r,k);
}

int main()
{
    int x,y,Q;
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    Build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        x=read();y=read();
        Insert(1,1,n,x,y,i);
        rest[i]=y-x+1;
    }
    for(Q=read();Q;Q--)
    {
        x=(read()+ans-1)%n+1;
        Delete(1,1,n,x);
        print(ans);
    }
    flush();
    return 0;
}