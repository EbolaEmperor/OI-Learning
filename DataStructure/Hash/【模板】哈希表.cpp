#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
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
	inline LL read()
	{
		LL x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush()
	{
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x)
	{
		*oS++ =x;
		if(oS==oT) flush();
	}
	template <class I>
	inline void print(I x)
	{
		if(!x) putc('0');
		while(x) qu[++ qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}
using namespace IO;

const int base=30321713,N=10000010;
int h[base],nxt[N],tot,pos[N];
LL num[N];

void push(LL x,int p)
{
	int s=x%base,i;
	for(i=h[s];nxt[i];i=nxt[i]);
	num[++tot]=x;
	pos[tot]=p;
	if(i) nxt[i]=tot;
	else h[s]=tot;
}

int find(LL x)
{
	int s=x%base;
	for(int i=h[s];i;i=nxt[i])
		if(num[i]==x) return pos[i];
}

int main()
{
	LL x,n=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		push(x,i);
	}
	int m=read();
	for(int i=1;i<=m;i++)
	{
		x=read();
		print(find(x));
	}
	flush();
	return 0;
}
