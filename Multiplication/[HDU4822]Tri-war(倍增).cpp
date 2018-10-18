#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}
void write(int x)
{
	if(x/10) write(x/10);
	putchar(x%10+'0');
}

const int N=100010;
struct Node{int ty,x;};
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;
int fa[18][N];
int dep[N],size[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int la)
{
	fa[0][u]=la;size[u]=1;
	for(int i=1;i<=16;i++)
		fa[i][u]=fa[i-1][fa[i-1][u]];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		size[u]+=size[v];
	}
}

int LCA(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=16;i>=0;i--)
		if(dep[fa[i][u]]>=dep[v]) u=fa[i][u];
	for(int i=16;i>=0;i--)
		if(fa[i][u]!=fa[i][v]) u=fa[i][u],v=fa[i][v];
	if(u!=v) u=fa[0][u];
	return u;
}

int jump(int u,int len)
{
	for(int i=16;i>=0;i--)
		if(1<<i<=len) u=fa[i][u],len-=1<<i;
	return u;
}

Node getmid(int u,int v,int lca)
{
	int len=dep[u]+dep[v]-2*dep[lca];
	if(dep[u]>=dep[v]) return Node{1,jump(u,(len-1)/2)};
	else return Node{2,jump(v,len/2)};
}

int gao(int a,int b,int c,int lab,int lac)
{
	Node ab=getmid(a,b,lab),ac=getmid(a,c,lac);
	if(ab.ty==1&&ac.ty==1)
		return dep[ab.x]>dep[ac.x]?size[ab.x]:size[ac.x];
	if(ab.ty==2&&ac.ty==2)
	{
		if(dep[ab.x]<dep[ac.x]) swap(ab,ac);
		if(LCA(ab.x,ac.x)==ac.x) return n-size[ac.x];
		else return n-size[ab.x]-size[ac.x];
	}
	if(ab.ty>ac.ty) swap(ab,ac),swap(b,c);
	if(LCA(ab.x,ac.x)==ab.x) return size[ab.x]-size[ac.x];
	else return size[ab.x];
}

int main()
{
	int T,a,b,c,Q;
	for(T=read();T;T--)
	{
		memset(h,0,sizeof(h));
		sum=0;n=read();
		for(int i=1;i<n;i++)
		{
			a=read();b=read();
			add_edge(a,b);
			add_edge(b,a);
		}
		dep[1]=1;dfs(1,0);
		Q=read();
		while(Q--)
		{
			a=read();b=read();c=read();
			int lab=LCA(a,b),lac=LCA(a,c),lbc=LCA(b,c);
			int ans1=gao(a,b,c,lab,lac);
			int ans2=gao(b,a,c,lab,lbc);
			int ans3=gao(c,a,b,lac,lbc);
			printf("%d %d %d\n",ans1,ans2,ans3);
		}
	}
	return 0;
}
