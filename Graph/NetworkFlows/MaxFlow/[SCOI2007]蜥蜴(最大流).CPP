#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

template <typename T> class Maxflow
{
	#define INF 0x7fffffff
	private:

	struct Edge{int from,to,next;T flow,capa;} e[2000000];
	int h[5000];
	int s,t,sum;
	int d[5000],cur[5000];
	bool vis[5000];

	void AddEdge(int u,int v,T w)
	{
		sum++;
		e[sum].from=u;
		e[sum].to=v;
		e[sum].capa=w;
		e[sum].flow=0;
		e[sum].next=h[u];
		h[u]=sum;
	}

	bool BFS()
	{
		queue<int> q;
		memset(vis,0,sizeof(vis));
		vis[s]=1;
		d[s]=0;
		q.push(s);
		while(!q.empty())
		{
			int o=q.front();
			for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			{
				if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
				{
					vis[e[tmp].to]=1;
					d[e[tmp].to]=d[o]+1;
					q.push(e[tmp].to);
				}
			}
			q.pop();
		}
		return vis[t];
	}

	T DFS(int u,T a)
	{
		T flow=0,f;
		if(u==t||a==0) return a;
		for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
		{
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
		}
		return flow;
	}
	
	public:
	
	T Dinic()
	{
		T flow=0;
		while(BFS())
		{
			for(int i=s;i<=t;i++) cur[i]=h[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
	
	void add_edge(int u,int v,T w)
	{
		AddEdge(u,v,w);
		AddEdge(v,u,0);
	}
	
	void init(int x,int y)
	{
		sum=-1;
		s=x;t=y;
		for(int i=s;i<=t;i++) h[i]=-1;
	}

};

int r,c,d;

#define IN 0
#define OUT 1
int getn(int x,int y,bool type)
{
	int n=(x-1)*c+y;
	return n+type*r*c;
}

int dist(int x1,int y1,int x2,int y2)
{
	int x=x1-x2;
	int y=y1-y2;
	return x*x+y*y;
}

int main()
{
	cin>>r>>c>>d;
	Maxflow<int> MF;
	MF.init(0,2*r*c+1);
	char ch;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			cin>>ch;
			if(ch!='0') MF.add_edge(getn(i,j,IN),getn(i,j,OUT),ch-'0');
		}
	int cnt=0;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
		{
			cin>>ch;
			if(ch=='L') MF.add_edge(0,getn(i,j,IN),1),cnt++;
		}
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			for(int ii=1;ii<=r;ii++)
				for(int jj=1;jj<=c;jj++)
				{
					if(i==ii&&j==jj) continue;
					if(dist(i,j,ii,jj)<=d*d) MF.add_edge(getn(i,j,OUT),getn(ii,jj,IN),INF);
				}
	for(int i=1;i<=r;i++)
	    for(int j=1;j<=c;j++)
	        if(i-d<1||i+d>r||j-d<1||j+d>c) MF.add_edge(getn(i,j,OUT),2*r*c+1,INF);
	int ans=MF.Dinic();
	cout<<(cnt-ans)<<endl;
	return 0;
}
