#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=200010;
int ch[N][2],fa[N],size[N],tot=0;
int mx[N],mn[N],val[N];
int delta[N],mndelta[N];
int a[N],rt=0;

void maintain(int x)
{
	mndelta[x]=min(delta[x],min(mndelta[ch[x][0]],mndelta[ch[x][1]]));
	mn[x]=min(val[x],min(mn[ch[x][0]],mn[ch[x][1]]));
	mx[x]=max(val[x],max(mx[ch[x][0]],mx[ch[x][1]]));
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}

void rotate(int x,int &rt)
{
	int y=fa[x],z=fa[y];
	int k=ch[y][1]==x,w=ch[x][k^1];
	if(y==rt) rt=x;
	else ch[z][ch[z][1]==y]=x;
	fa[x]=z;
	ch[y][k]=w;fa[w]=y;
	ch[x][k^1]=y;fa[y]=x;
	maintain(y);
	maintain(x);
}

void splay(int x,int &rt)
{
	int y,z;
	while(x!=rt)
	{
		y=fa[x];z=fa[y];
		if(y!=rt) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y,rt);
		rotate(x,rt);
	}
}

void build(int& o,int l,int r,int f)
{
	int mid=(l+r)/2;o=++tot;
	val[o]=mx[o]=mn[o]=a[mid];
	mndelta[o]=delta[o]=abs(a[mid+1]-a[mid]);
	fa[o]=f;size[o]=1;
	if(l<mid) build(ch[o][0],l,mid-1,o);
	if(r>mid) build(ch[o][1],mid+1,r,o);
	maintain(o);
}

int kth(int x,int k)
{
	if(size[ch[x][0]]+1==k) return x;
	if(size[ch[x][0]]>=k) return kth(ch[x][0],k);
	return kth(ch[x][1],k-size[ch[x][0]]-1);
}

void insert(int x,int k)
{
	int a=kth(rt,x+1),b=kth(rt,x+2);
	splay(a,rt);splay(b,ch[rt][1]);
	ch[b][0]=++tot;
	fa[tot]=b;size[tot]=1;
	mn[tot]=mx[tot]=val[tot]=k;
	mndelta[tot]=delta[tot]=abs(k-val[b]);
	delta[a]=abs(k-val[a]);
	maintain(b);maintain(a);
}

void merge(int x,int k)
{
	int a=kth(rt,x),b=kth(rt,x+2),c=kth(rt,x+3);
	splay(a,rt);splay(b,ch[rt][1]);
	ch[b][0]=fa[ch[b][0]]=0;
	val[b]=mn[b]=mx[b]=k;
	delta[a]=abs(val[a]-k);
	delta[b]=mndelta[b]=abs(val[c]-k);
	maintain(b);maintain(a);
}

int Query1(int l,int r)
{
	int a=kth(rt,l),b=kth(rt,r+2);
	splay(a,rt);splay(b,ch[rt][1]);
	return mx[ch[b][0]]-mn[ch[b][0]];
}

int Query2(int l,int r)
{
	int a=kth(rt,l),b=kth(rt,r+1);
	splay(a,rt);splay(b,ch[rt][1]);
	return mndelta[ch[b][0]];
}

int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	mn[0]=mndelta[0]=INF;mx[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	build(rt,0,n+1,0);
	static char opt[10];
	while(m--)
	{
		scanf("%s%d%d",opt,&x,&y);
		if(opt[2]=='x') printf("%d\n",Query1(x,y));
		if(opt[2]=='n') printf("%d\n",Query2(x,y));
		if(opt[2]=='r') merge(x,y);
		if(opt[2]=='s') insert(x,y);
	}
	return 0;
}
