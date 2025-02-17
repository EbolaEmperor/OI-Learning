#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=1<<16;
	//Input Correlation
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
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}

using namespace IO;
typedef long long LL;
const int N=200010;
int a[N],n,m,block;
struct Qry{int l,r,id;} q[N];
int sum[N*5];
LL ans[N];

bool operator < (const Qry &a,const Qry &b){return a.l/block<b.l/block||a.l/block==b.l/block&&a.r<b.r;}

LL gao(int p,int k)
{
	LL res=0;
	res-=1ll*a[p]*sum[a[p]]*sum[a[p]];
	sum[a[p]]+=k;
	res+=1ll*a[p]*sum[a[p]]*sum[a[p]];
	return res;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i;
	block=sqrt(n);
	sort(q+1,q+1+m);
	int pl=0,pr=0;LL now=0;
	for(int i=1;i<=m;i++)
	{
		while(pl<q[i].l) now+=gao(pl,-1),pl++;
		while(pl>q[i].l) pl--,now+=gao(pl,1);
		while(pr>q[i].r) now+=gao(pr,-1),pr--;
		while(pr<q[i].r) pr++,now+=gao(pr,1);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;i++) print(ans[i]);
	flush();
	return 0;
}
