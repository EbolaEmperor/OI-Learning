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
	inline void reads(char *s)
	{
		char c=Get();int tot=0;
		while(c<'a'||c>'z') c=Get();
		while(c>='a'&&c<='z') s[++tot]=c,c=Get();
		s[++tot]='\0';
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
	}
}

using namespace IO;
const int N=1200010;
int ch[N][27],prt[N],len[N];
int m,lst=1,tot=1,topo[N];
int mul[22][N],pos[N];
char s[N],b[N];
int root[N];

void Extend(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
}

void TopoSort()
{
	static int c[N];
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<=tot;i++) c[i]+=c[i-1];
	for(int i=1;i<=tot;i++) topo[c[len[i]]--]=i;
}

typedef pair<int,int> pii;
int ls[N*22],rs[N*22],sz=0;
pii data[N*22];

pii operator + (const pii &a,const pii &b)
{
	if(a.second>b.second) return a;
	if(a.second<b.second) return b;
	return a.first<b.first?a:b;
}

void Insert(int &o,int k,int l=1,int r=m)
{
	if(!o) o=++sz;
	if(l==r){data[o]=pii(l,data[o].second+1);return;}
	int mid=(l+r)/2;
	if(k<=mid) Insert(ls[o],k,l,mid);
	else Insert(rs[o],k,mid+1,r);
	data[o]=data[ls[o]]+data[rs[o]];
}

int Merge(int L,int R,int l=1,int r=m)
{
	if(!L||!R) return L+R;
	int o=++sz;
	if(l==r){data[o]=pii(l,data[L].second+data[R].second);return o;}
	int mid=(l+r)/2;
	ls[o]=Merge(ls[L],ls[R],l,mid);
	rs[o]=Merge(rs[L],rs[R],mid+1,r);
	data[o]=data[ls[o]]+data[rs[o]];
	return o;
}

pii Query(int nl,int nr,int o,int l=1,int r=m)
{
	if(!o) return pii(0,0);
	if(l==nl&&r==nr) return data[o];
	int mid=(l+r)/2;
	if(nr<=mid) return Query(nl,nr,ls[o],l,mid);
	if(nl>mid) return Query(nl,nr,rs[o],mid+1,r);
	return Query(nl,mid,ls[o],l,mid)+Query(mid+1,nr,rs[o],mid+1,r);
}

void Init()
{
	TopoSort();
	for(int i=tot;i>=1;i--)
	{
		int u=topo[i];
		if(prt[u]) root[prt[u]]=Merge(root[prt[u]],root[u]);
	}
	for(int i=1;i<=tot;i++) mul[0][i]=prt[i];
	for(int i=1;i<=20;i++)
		for(int j=1;j<=tot;j++)
			mul[i][j]=mul[i-1][mul[i-1][j]];
}

int find(int l,int r)
{
	int n=r-l+1,p=pos[r];
	for(int i=20;i>=0;i--)
		if(len[mul[i][p]]>=n) p=mul[i][p];
	return p;
}

int main()
{
	reads(s);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
		Extend(s[i]-'a'),pos[i]=lst;
	Extend(26);
	m=read();
	for(int i=1;i<=m;i++)
	{
		reads(b);
		len=strlen(b+1);
		for(int j=1;j<=len;j++)
			Extend(b[j]-'a'),Insert(root[lst],i);
		Extend(26);
	}
	Init();
	int Q=read(),l,r,pl,pr;
	while(Q--)
	{
		l=read();r=read();
		pl=read();pr=read();
		int x=find(pl,pr);
		pii ans=Query(l,r,root[x]);
		if(!ans.second) ans.first=l;
		print(ans.first);putc(' ');
		print(ans.second);putc('\n');
	}
	flush();
	return 0;
}
