#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

namespace MF
{
	struct Edge{int to,capa,next,flow;} e[2000000];
	int h[5000],sum=-1,s,t;
	int cur[5000],d[5000];
	bool vis[5000];
	void init()
	{
		sum=-1;
		for(int i=s;i<=t;i++) h[i]=-1;
	}
	void AddEdge(int u,int v,int w)
	{
		sum++;
		e[sum].to=v;
		e[sum].capa=w;
		e[sum].flow=0;
		e[sum].next=h[u];
		h[u]=sum;
	}
	void add_edge(int u,int v,int w)
	{
		AddEdge(u,v,w);
		AddEdge(v,u,0);
	}
	int DFS(int u,int a)
	{
		if(u==t||a==0) return a;
		int flow=0,f;
		for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
			if(d[e[tmp].to]==d[u]+1)
			{
				f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
				if(f>0)
				{
					flow+=f;
					a-=f;
					e[tmp].flow+=f;
					e[tmp^1].flow-=f;
					if(a==0) break;
				}
			}
		return flow;
	}
	bool BFS()
	{
		queue<int> q;
		q.push(s);
		memset(vis,0,sizeof(vis));
		vis[s]=1;d[s]=0;
		while(!q.empty())
		{
			int o=q.front();
			for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
				if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
				{
					vis[e[tmp].to]=1;
					d[e[tmp].to]=d[o]+1;
					q.push(e[tmp].to);
				}
			q.pop();
		}
		return vis[t];
	}
	int work()
	{
		int flow=0;
		while(BFS())
		{
			for(int i=s;i<=t;i++) cur[i]=h[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
}

namespace LIS
{
	int a[1000],f[1000];
	int work(int n)
	{
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			f[i]=1;
			for(int j=1;j<i;j++)
				if(a[j]<=a[i]) f[i]=max(f[i],f[j]+1);
			ans=max(ans,f[i]);
		}
		return ans;
	}
}

int main()
{
	int n;
	cin>>n;
	MF::s=0;
	MF::t=2*n+1;
	for(int i=1;i<=n;i++)
		scanf("%d",LIS::a+i);
	int ans1=LIS::work(n);
	cout<<ans1<<endl;
	MF::init();
	for(int i=1;i<=n;i++)
	{
		if(LIS::f[i]==1) MF::add_edge(MF::s,i,1);
		if(LIS::f[i]==ans1) MF::add_edge(i+n,MF::t,1);
		MF::add_edge(i,i+n,1);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if(LIS::a[j]<=LIS::a[i]&&LIS::f[j]+1==LIS::f[i]) MF::add_edge(j+n,i,1);
	int ans2=MF::work();
	cout<<ans2<<endl;
	if(LIS::f[n]==ans1)
	{
		MF::add_edge(n,n+n,INF);
		MF::add_edge(n+n,MF::t,INF);
		MF::add_edge(1,1+n,INF);
		MF::add_edge(MF::s,1,INF);
	}
	int ans3=ans2+MF::work();
	cout<<ans3<<endl;
	return 0;
}
