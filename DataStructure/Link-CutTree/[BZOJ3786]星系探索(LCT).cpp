#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
int ch[N][2],fa[N],size[N],n;
LL sum[N],sumtag[N],tag[N],val[N];

inline bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void maintain(int x)
{
	sum[x]=val[x];sumtag[x]=tag[x];size[x]=1;
	if(ch[x][0])
	{
		sum[x]+=sum[ch[x][0]]+sumtag[ch[x][0]];
		sumtag[x]+=sumtag[ch[x][0]];
		size[x]+=size[ch[x][0]];
	}
	if(ch[x][1])
	{
		sum[x]+=sum[ch[x][1]]+sumtag[x]*size[ch[x][1]];
		sumtag[x]+=sumtag[ch[x][1]];
		size[x]+=size[ch[x][1]];
	}
}

void rotate(int x)
{
	int y=fa[x],z=fa[y];
	int k=ch[y][1]==x,w=ch[x][k^1];
	if(nroot(y)) ch[z][ch[z][1]==y]=x;
	ch[x][k^1]=y;
	ch[y][k]=w;
	if(w) fa[w]=y;
	fa[y]=x;fa[x]=z;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y,z;
	while(nroot(x))
	{
		y=fa[x],z=fa[y];
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

void change(int x,int y)
{
	access(x);splay(x);
	fa[ch[x][0]]=0;ch[x][0]=0;
	access(y);splay(y);
	LL t=sumtag[x]-tag[x]-sumtag[y];
	val[x]+=t;tag[x]+=t;
	sum[x]=val[x];sumtag[x]=tag[x];
	size[x]=1;fa[x]=y;
	access(x);splay(x);
}

void Add(int x,int k)
{
	access(x);splay(x);
	sum[x]+=k;sumtag[x]+=k;
	tag[x]+=k;val[x]+=k;
}

int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
		scanf("%d",fa+i);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",val+i);
		sum[i]=val[i];
		size[i]=1;
	}
	int Q,x,y;static char opt[5];
	for(scanf("%d",&Q);Q;Q--)
	{
		scanf("%s%d",opt,&x);
		if(opt[0]=='C'){scanf("%d",&y);change(x,y);}
		if(opt[0]=='F'){scanf("%d",&y);Add(x,y);}
		if(opt[0]=='Q'){access(x);splay(x);printf("%lld\n",sum[x]);}
	}
}
