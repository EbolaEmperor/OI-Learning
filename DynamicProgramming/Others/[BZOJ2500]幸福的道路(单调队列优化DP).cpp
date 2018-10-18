#include<bits/stdc++.h>
using namespace std;

const int S=1<<20;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
template<typename I>inline void read(I &x)
{
	x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
}

typedef long long LL;
const int N=1000010;
struct Edge{int to,next;LL capa;} e[N];
int h[N],sum=0,n,m;
LL f1[N],f2[N],g[N];
int lson[N],ans=0;
deque<int> q1,q2;

void add_edge(int u,int v,LL w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;dfs1(v);
		LL res=f1[v]+e[tmp].capa;
		if(res>f1[u])
		{
			f2[u]=f1[u];
			f1[u]=res;
			lson[u]=v;
		}
		else if(res>f2[u]) f2[u]=res;
	}
}

void dfs2(int u,LL dis)
{
	g[u]=max(f1[u],dis);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==lson[u]) dfs2(v,max(f2[u]+e[tmp].capa,dis+e[tmp].capa));
		else dfs2(v,max(f1[u]+e[tmp].capa,dis+e[tmp].capa));
	}
}

void gao()
{
	for(int i=1,k=1;i<=n;i++)
	{
		while(!q1.empty()&&g[i]<=g[q1.back()]) q1.pop_back();
		while(!q2.empty()&&g[i]>=g[q2.back()]) q2.pop_back();
		q1.push_back(i);q2.push_back(i);
		while(g[q2.front()]-g[q1.front()]>m)
			if(q2.front()<q1.front()) k=q2.front()+1,q2.pop_front();
			else k=q1.front()+1,q1.pop_front();
		ans=max(ans,i-k+1);
	}
}

int main()
{
	int fa;LL w;
	read(n);read(m);
	for(int i=2;i<=n;i++)
	{
		read(fa);read(w);
		add_edge(fa,i,w);
	}
	dfs1(1);dfs2(1,0);gao();
	printf("%d\n",ans);
	return 0;
}
