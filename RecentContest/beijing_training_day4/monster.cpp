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

const int ha=1e9+7;
const int N=100010,S=320;
int a[N],b[N],n,q,fst;
int bg[S],ed[S],dv[N],tot;
int f[S][S],g[S][S],cnt[S];
// f[i]: 第i个块里选premax的所有位置对应的premax 
// g[i]: 第i个块里选premax的所有位置对应的a
int iprodf[S][S],prodg[S][S];
// iprodf[i][j]: f[i][1]*f[i][2]*...*f[i][j]的逆元 
// prodg[i][j]: g[i][1]*g[i][2]*...*g[i][j]
int val[S],mx[S];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void divide()
{
	tot=1;
	for(int i=1,cnt=0;i<=n;i++)
	{
		if(!cnt) bg[tot]=i;
		dv[i]=tot;cnt++;
		if(cnt==S) ed[tot]=i,cnt=0,tot++;
	}
	ed[tot]=n;
}

void build(int id)
{
	int premax=1;val[id]=1;cnt[id]=0;
	for(int i=bg[id];i<=ed[id];i++)
	{
		val[id]=1ll*val[id]*min(a[i],premax)%ha;
		if(premax<a[i])
		{
			cnt[id]++;
			f[id][cnt[id]]=premax;
			g[id][cnt[id]]=a[i];
		}
		premax=max(premax,b[i]);
	}
	mx[id]=premax;
	sort(g[id]+1,g[id]+1+cnt[id]);
	iprodf[id][0]=prodg[id][0]=1;
	for(int i=1;i<=cnt[id];i++) iprodf[id][i]=1ll*iprodf[id][i-1]*f[id][i]%ha;
	for(int i=1;i<=cnt[id];i++) prodg[id][i]=1ll*prodg[id][i-1]*g[id][i]%ha;
	iprodf[id][cnt[id]]=Pow(iprodf[id][cnt[id]],ha-2);
	for(int i=cnt[id]-1;i>=1;i--) iprodf[id][i]=1ll*iprodf[id][i+1]*f[id][i+1]%ha;
}

int getans()
{
	int premax=fst,ans=1;
	for(int i=1;i<=tot;i++)
	{
		int x=upper_bound(f[i]+1,f[i]+cnt[i]+1,premax)-f[i]-1;
		int y=upper_bound(g[i]+1,g[i]+cnt[i]+1,premax)-g[i]-1;
		ans=1ll*ans*val[i]%ha*iprodf[i][x]%ha*prodg[i][y]%ha*Pow(premax,x-y)%ha;
		premax=max(premax,mx[i]);
	}
	return ans;
}

int main()
{
	using IO::read;
	using IO::print;
	n=read();q=read();fst=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	divide();
	for(int i=1;i<=tot;i++) build(i);
	print(getans());
	int opt,x,y;
	while(q--)
	{
		opt=read();x=read();y=read();
		(opt?b[x]:a[x])=y;
		build(dv[x]);
		print(getans());
	}
	return IO::flush(),0;
}
