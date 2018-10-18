#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
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
		putc(' ');
	}
}

using namespace IO;
typedef unsigned int uint;
const int N=200010;
struct Seg
{
	uint l,r,id;
	Seg(uint a=0,uint b=0,uint c=0):l(a),r(b),id(c){}
	friend bool operator < (const Seg &a,const Seg &b){return a.l<b.l;}
} seg[N<<1];
int mul[19][N<<1];
int ans[N];
uint n,m;

void Init()
{
	sort(seg+1,seg+1+2*n);
	int pr=0;
	seg[2*n+1]=Seg(-1,-1);
	for(int i=1;i<=2*n;i++)
	{
		while(seg[pr+1].l<=seg[i].r) pr++;
		mul[0][i]=pr;
	}
	for(int j=1;j<=18;j++)
		for(int i=1;i<=2*n;i++)
			mul[j][i]=mul[j-1][mul[j-1][i]];
	seg[0]=Seg(-1,-1);
}

int main()
{
	uint l,r;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		l=read();r=read();
		if(l<=r)
		{
			seg[i]=Seg(l,r,i);
			seg[n+i]=Seg(m+l,m+r);
		}
		else
		{
			seg[i]=Seg(l,m+r,i);
			seg[n+i]=Seg(m+l,m*2+r);
		}
	}
	Init();
	for(int i=1;i<=2*n;i++)
	{
		if(!seg[i].id) continue;
		int p=i,res=2;
		for(int j=18;j>=0;j--)
			if(seg[mul[j][p]].r-seg[i].l<m)
				p=mul[j][p],res+=1<<j;
		ans[seg[i].id]=res;
	}
	for(int i=1;i<=n;i++) print(ans[i]);
	flush();
	return 0;
}
