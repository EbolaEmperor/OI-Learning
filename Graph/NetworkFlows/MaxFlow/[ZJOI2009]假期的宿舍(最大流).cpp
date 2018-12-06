#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[3000],a[3000],p[3000],d[3000],cur[3000];
bool home[3000],school[3000];
int sum;
bool vis[3000];
int n;
int s,t;

void add_edge(int u,int v,int c)
{
    sum++;
    e[sum].from=u;
    e[sum].to=v;
    e[sum].capa=c;
    e[sum].flow=0;
    e[sum].next=h[u];
    h[u]=sum;
}

bool BFS()
{
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);
    d[s]=0;
    vis[s]=1;
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

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int& tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
    {
        if(d[u]+1==d[e[tmp].to])
        {
            f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(f>0)
            {
                e[tmp].flow+=f;
                e[tmp^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
    }
    return flow;
}

int MaxFlow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=2*n+100;i++) cur[i]=h[i];
        flow+=DFS(s,0x7fffffff);
    }
    return flow;
}

int main()
{
	int tt;
	cin>>tt;
	for(int T=1;T<=tt;T++)
	{
		int u,cnt=0;
		sum=-1;
		cin>>n;
		for(int i=0;i<=n+100;i++) h[i]=-1;
		memset(&e,0,sizeof(e));
		memset(home,0,sizeof(home));
		s=0;
		for(int i=1;i<=n;i++) scanf("%d",school+i);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&u);
			if(school[i]&&u==1) home[i]=true;
		}
		t=2*n+1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				scanf("%d",&u);
				if(u==1||i==j)
				{
					add_edge(i,j+n,1);
					add_edge(j+n,i,0);
				}
			}
		for(int i=1;i<=n;i++)
		{
			if(school[i])
			{
				add_edge(i+n,t,1);
				add_edge(t,i+n,0);
			}
			if(!home[i])
			{
				add_edge(s,i,1);
				add_edge(i,s,0);
				cnt++;
			}
		}
		if(MaxFlow()>=cnt) printf("^_^\n"); else printf("T_T\n");
	}
    return 0;
}
