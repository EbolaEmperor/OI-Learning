#include<bits/stdc++.h>
#define newtrie(x) x=new Trie,x->ch[0]=x->ch[1]=null
using namespace std;

struct Edge{int to,capa,next;} e[200010];
int h[100010],sum=0;
int dis[100010];
struct Trie
{
	Trie *ch[2];
	Trie(){ch[0]=ch[1]=NULL;}
};
Trie *rt,*null;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		dis[e[tmp].to]=dis[u]^e[tmp].capa;
		dfs(e[tmp].to,u);
	}
}

void insert(int x)
{
	Trie *p=rt;
	for(int i=30;i>=0;i--)
	{
		int j=(x>>i)&1;
		if(p->ch[j]==null) newtrie(p->ch[j]);
		p=p->ch[j];
	}
}

int query(int x)
{
	Trie *p=rt;
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int j=((x>>i)&1)^1;
		if(p->ch[j]!=null) ans|=(1<<i);
		else j^=1;
		p=p->ch[j];
	}
	return ans;
}

int main()
{
	newtrie(null);
	newtrie(rt);
	int n,u,v,w;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) insert(dis[i]);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,query(dis[i]));
	cout<<ans<<endl;
	return 0;
}
