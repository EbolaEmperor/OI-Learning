#include<bits/stdc++.h>
#define ha 10007
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
		putc('\n');
	}
}

using namespace IO;
const int N=30010;
int ch[N][2],fa[N],sfa[N];
struct Equ
{
	int k,b;
	Equ(int _k=0,int _b=0):k(_k),b(_b){}
	int get(int x){return (k*x+b)%ha;}
	friend Equ operator + (const Equ &a,const Equ &b){return Equ(a.k*b.k%ha,(a.k*b.b+a.b)%ha);}
} sum[N],val[N];

int f[N];
int findfa(int x){return f[x]==x?x:f[x]=findfa(f[x]);}

inline bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void maintain(int x)
{
	sum[x]=val[x];
	if(ch[x][0]) sum[x]=sum[x]+sum[ch[x][0]];
	if(ch[x][1]) sum[x]=sum[ch[x][1]]+sum[x];
}

void rotate(int x)
{
	int y=fa[x],z=fa[y];
	int k=ch[y][1]==x,w=ch[x][k^1];
	if(nroot(y)) ch[z][ch[z][1]==y]=x;
	ch[x][k^1]=y;ch[y][k]=w;
	if(w) fa[w]=y;
	fa[x]=z;fa[y]=x;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y,z;
	while(nroot(x))
	{
		y=fa[x];z=fa[y];
		if(nroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
		rotate(x);
	}
}

void access(int x)
{
	for(int y=0;x;y=x,x=fa[x])
	{
		splay(x);
		ch[x][1]=y;
		maintain(x);
	}
}

int find(int x)
{
	access(x);splay(x);
	while(ch[x][0]) x=ch[x][0];
	return x;
}

void cut(int x)
{
	access(x);splay(x);
	fa[ch[x][0]]=0;
	ch[x][0]=0;
	maintain(x);
}

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=a*a%ha)
		if(b&1) ans=ans*a%ha;
	return ans;
}

int main()
{
	int n=read(),m,a,k,p,b;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=n;i++)
	{
		k=read();p=read();b=read();
		val[i]=Equ(k,b);
		if(findfa(p)==i) sfa[i]=p;
		else fa[i]=p,f[findfa(i)]=findfa(p);
	}
	char opt;
	for(m=read();m;m--)
	{
		opt=Get();
		while(opt!='A'&&opt!='C') opt=Get();
		a=read();
		if(opt=='A')
		{
			int rt=find(a),s=sfa[rt];
			access(s);splay(s);
			if(sum[s].k==1)
			{
				if(sum[s].b==0) puts("-2");
				else puts("-1");
				continue;
			}
			int x=(sum[s].b*Pow(1-sum[s].k,ha-2)%ha+ha)%ha;
			access(a);splay(a);
			print(sum[a].get(x));
		}
		if(opt=='C')
		{
			k=read();p=read();b=read();
			val[a].k=k;val[a].b=b;
			int rt=find(a);
			if(a==rt) sfa[a]=0;
			else
			{
				cut(a);
				if(find(sfa[rt])==a)
				{
					splay(rt);
					fa[rt]=sfa[rt];
					sfa[rt]=0;
				}
			}
			splay(a);
			if(find(p)==a) sfa[a]=p;
			else fa[a]=p;
		}
	}
	flush();
	return 0;
}
