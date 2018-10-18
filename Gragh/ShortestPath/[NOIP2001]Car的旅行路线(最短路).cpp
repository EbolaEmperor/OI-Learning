#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
} p[500];
int s,t,a,b;
int cost[105];
struct Edge
{
	int to,next;
	double capa;
	void clear(){to=0;capa=0.0;next=0;}
} e[500000];
int h[500];
bool vis[500];
double dist[500];
int sum;

void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
}
void read(Point &a){read(a.x);read(a.y);}
void swap(Point &a,Point &b){Point t=a;a=b;b=t;}

Point operator + (const Point &a,const Point &b){return Point(a.x+b.x,a.y+b.y);}
Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
int operator * (const Point &a,const Point &b){return a.x*b.x+a.y*b.y;}
double Dist(Point a,Point b){return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));}

void add_edge(int u,int v,double w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

int main()
{
	int T;
	for(read(T);T>0;T--)
	{
		read(s);read(t);read(a);read(b);
		for(int i=0;i<s;i++)
		{
			read(p[4*i+1]);
			read(p[4*i+2]);
			read(p[4*i+3]);
			read(cost[i]);
			if((p[4*i+1]-p[4*i+2])*(p[4*i+3]-p[4*i+2])==0) swap(p[4*i+1],p[4*i+2]);
			if((p[4*i+1]-p[4*i+3])*(p[4*i+2]-p[4*i+3])==0) swap(p[4*i+1],p[4*i+3]);
			p[4*i+4]=p[4*i+2]+(p[4*i+3]-p[4*i+1]);
		}
		for(int i=0;i<500000;i++) e[i].clear();
		sum=0;
		memset(h,0,sizeof(h));
		for(int i=1;i<4*s;i++)
			for(int j=i+1;j<=4*s;j++)
				if((i-1)/4==(j-1)/4)
				{
					add_edge(i,j,(double)cost[i/4]*Dist(p[i],p[j]));
					add_edge(j,i,(double)cost[i/4]*Dist(p[i],p[j]));
				}
				else 
				{
					add_edge(i,j,(double)t*Dist(p[i],p[j]));
					add_edge(j,i,(double)t*Dist(p[i],p[j]));
				}
		memset(vis,0,sizeof(vis));
		queue<int> q;
		for(int i=1;i<=4*s;i++) dist[i]=INF;
		for(int i=1;i<=4;i++)
		{
			q.push(4*(a-1)+i);
			vis[4*(a-1)+i]=1;
			dist[4*(a-1)+i]=0.0;
		}
		while(!q.empty())
		{
			int o=q.front();
			for(int tmp=h[o];tmp;tmp=e[tmp].next)
			{
				if(e[tmp].capa+dist[o]<dist[e[tmp].to])
				{
					dist[e[tmp].to]=e[tmp].capa+dist[o];
					if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
				}
			}
			q.pop();
			vis[o]=0;
		}
		double ans=min(min(dist[4*(b-1)+1],dist[4*(b-1)+2]),min(dist[4*(b-1)+3],dist[4*(b-1)+4]));
		printf("%.1lf\n",ans);
	}
	return 0;
}
