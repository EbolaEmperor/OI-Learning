#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=1<<20;
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
typedef pair<int,int> pii;
const int N=50010;
int n,m,block,a[N];
struct Qry{int l,r,up,id;} q[N];
int exL[N],exR[N],ans[N];
pii tmp[N];

bool operator < (const Qry &a,const Qry &b){return a.up<b.up||a.up==b.up&&a.r<b.r;}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	block=sqrt(n);
	for(int i=1;i<=m;i++)
	{
		q[i].l=read();
		q[i].r=read();
		q[i].id=i;
		q[i].up=(q[i].l+block-1)/block*block;
	}
	sort(q+1,q+1+m);
	int pr,res;
	for(int i=1;i<=m;i++)
	{
		if(q[i].up!=q[i-1].up)
		{
			res=0;pr=q[i].up;
			memset(exL,0,sizeof(exL));
			memset(exR,0,sizeof(exR));
		}
		while(pr<q[i].r)
		{
			pr++;
			exL[a[pr]]=exL[a[pr]-1]+1;
			exR[a[pr]]=exR[a[pr]+1]+1;
			int t=exL[a[pr]]+exR[a[pr]]-1;
			int x=a[pr]-exL[a[pr]]+1,y=a[pr]+exR[a[pr]]-1;
			res=max(res,t);
			exR[x]=exL[y]=t;
		}
		int top=0,tres=res;
		for(int pl=q[i].l;pl<=q[i].up&&pl<=q[i].r;pl++)
		{
			exL[a[pl]]=exL[a[pl]-1]+1;
			exR[a[pl]]=exR[a[pl]+1]+1;
			int t=exL[a[pl]]+exR[a[pl]]-1;
			int x=a[pl]-exL[a[pl]]+1,y=a[pl]+exR[a[pl]]-1;
			tres=max(tres,t);
			tmp[++top]=pii(x,exR[x]);
			tmp[++top]=pii(y,exL[y]);
			exR[x]=exL[y]=t;
		}
		ans[q[i].id]=tres;
		for(;top;top--)
			if(top&1) exR[tmp[top].first]=tmp[top].second;
			else exL[tmp[top].first]=tmp[top].second;
		for(int j=q[i].l;j<=q[i].up&&j<=q[i].r;j++)
			exL[a[j]]=exR[a[j]]=0;
	}
	for(int i=1;i<=m;i++) print(ans[i]);
	flush();
	return 0;
}
