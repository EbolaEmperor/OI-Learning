#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

int n,m;
double p[20][5];
int sum=0;
int h[200];
struct Edge{int to,next;double capa;} e[2000000];
double dist[200];
bool vis[200];

void add_edge(int u,int v,double w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_judge(int a,int b,int c,int d)
{
	double k=(p[b][d]-p[a][c])/(p[b][0]-p[a][0]);
	double bb=p[a][c]-k*p[a][0];
	bool flag=1;
	for(int i=a+1;i<b;i++)
	{
		double y=k*p[i][0]+bb;
		if(!((y>=p[i][1]&&y<=p[i][2])||(y>=p[i][3]&&y<=p[i][4]))) flag=0;
	}
	if(flag) add_edge(a*4+c,b*4+d,sqrt((p[b][d]-p[a][c])*(p[b][d]-p[a][c])+(p[b][0]-p[a][0])*(p[b][0]-p[a][0])));
}

void SPFA(int s,int t)
{
	for(int i=0;i<=4*(n+2);i++) dist[i]=0x7fffffff;
	dist[1]=dist[2]=dist[3]=dist[4]=0;
	memset(vis,0,sizeof(vis));
	vis[1]=vis[2]=vis[3]=vis[4]=1;
	queue<int> q;
	q.push(1);q.push(2);q.push(3);q.push(4);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp;tmp=e[tmp].next)
		{
			if(dist[o]+e[tmp].capa<dist[e[tmp].to])
			{
				dist[e[tmp].to]=dist[o]+e[tmp].capa;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf%lf%lf",&p[i][0],&p[i][1],&p[i][2],&p[i][3],&p[i][4]);
	p[0][0]=0.0,p[++n][0]=10.0;
	for(int i=1;i<5;i++) p[0][i]=p[n][i]=5.0;
	memset(h,0,sizeof(h));
	for(int i=0;i<n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=1;k<5;k++)
				for(int l=1;l<5;l++)
					add_judge(i,j,k,l);
	SPFA(1,4*n+1);
	printf("%.2lf\n",dist[4*n+1]);
	return 0;
}
