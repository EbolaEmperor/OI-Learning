#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int son[2];
	int fa,s;
} nd[200010];

inline void maintain(int x){nd[x].s=nd[ls].s+nd[rs].s+1;}
inline bool notroot(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}

void rotate(int x)
{
	int y=nd[x].fa,z=nd[y].fa;
	int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
	if(notroot(y)) nd[z].son[nd[z].son[1]==y]=x;
	nd[x].son[k^1]=y;
	nd[y].son[k]=w;
	if(w) nd[w].fa=y;
	nd[y].fa=x;
	nd[x].fa=z;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y,z;
	while(notroot(x))
	{
		y=nd[x].fa;
		z=nd[y].fa;
		if(notroot(y)) rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
		rotate(x);
	}
	maintain(x);
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		nd[x].son[1]=y;
		maintain(x);
		y=x;
		x=nd[x].fa;
	}
}

int main()
{
	int n,m,opt,x,y;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		nd[i].s=1;
		scanf("%d",&x);
		if(i+x<=n) nd[i].fa=i+x;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&opt,&x);x++;
		access(x);splay(x);
		if(opt==1)
			printf("%d\n",nd[x].s);
		else
		{
			scanf("%d",&y);
			nd[ls].fa=0;ls=0;
			if(x+y<=n) nd[x].fa=x+y;
			maintain(x);
		}
	}
	return 0;
}
