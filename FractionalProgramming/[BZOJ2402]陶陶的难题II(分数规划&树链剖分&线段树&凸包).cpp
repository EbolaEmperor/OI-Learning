#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
using namespace std;

const int N=300010;
const double eps=1e-5;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

struct Point
{
	double x,y;
	Point(double _=0,double __=0):x(_),y(__){}
	friend bool operator < (const Point &a,const Point &b){return dcmp(a.x-b.x)<0||dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)<0;}
	friend Point operator + (const Point &a,const Point &b){return Point(a.x+b.x,a.y+b.y);}
	friend Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
	friend double Cross(const Point &a,const Point &b){return a.x*b.y-a.y*b.x;}
	friend double Dot(const Point &a,const Point &b){return a.x*b.x+a.y*b.y;}
};

struct Node
{
	vector<Point> ch;
	void insert(Point p){ch.pb(p);}
	void merge(Node a,Node b)
	{
		int n1=a.ch.size(),n2=b.ch.size(),p1=0,p2=0,top=0;
		Point p;
		while(p1<n1||p2<n2)
		{
			if(p1==n1) p=b.ch[p2++];
			else if(p2==n2) p=a.ch[p1++];
			else if(a.ch[p1]<b.ch[p2]) p=a.ch[p1++];
			else p=b.ch[p2++];
			while(top>1&&dcmp(Cross(ch[top-1]-ch[top-2],p-ch[top-2]))>=0) top--,ch.pob();
			top++;ch.pb(p);
		}
	}
	double query(double d)
	{
		Point p=Point(-1e4*d,1e4),pt;
		int l=0,r=ch.size()-1,mid1,mid2;
		while(r-l>3)
		{
			mid1=(2*l+r)/3;mid2=(l+2*r)/3;
			if(dcmp(Dot(p,ch[mid1])-Dot(p,ch[mid2]))<=0) l=mid1;
			else r=mid2;
		}
		double ans=-1e12,tmp;
		for(int i=l;i<=r;i++)
		{
			tmp=Dot(p,ch[i]);
			if(tmp>ans) ans=tmp,pt=ch[i];
		}
		return pt.y-d*pt.x;
	}
};

struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int dfn[N],idex[N],dfc=0;
int top[N],fa[N],dep[N];
int size[N],hson[N];

void add_edge(int u,int v){e[++sum].to=v;e[sum].next=h[u];h[u]=sum;}

void dfs1(int u,int la)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;dfs1(v,u);
		fa[v]=u;size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;dfn[u]=++dfc;idex[dfc]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}

struct Segment
{
	Point pnt[N];
	Node v[N<<2];
	void Build(int o,int l,int r)
	{
		if(l==r){v[o].insert(pnt[idex[l]]);return;}
		int mid=(l+r)/2;
		Build(o*2,l,mid);
		Build(o*2+1,mid+1,r);
		v[o].merge(v[o*2],v[o*2+1]);
	}
	double Query(int o,int l,int r,int nl,int nr,double d)
	{
		if(l>=nl&&r<=nr) return v[o].query(d);
		int mid=(l+r)/2;double ans=-1e12;
		if(nl<=mid) ans=max(ans,Query(o*2,l,mid,nl,nr,d));
		if(nr>mid) ans=max(ans,Query(o*2+1,mid+1,r,nl,nr,d));
		return ans;
	}
} t1,t2;

Point Query(double x,int p1,int p2)
{
	Point ans=Point(-1e12,-1e12);
	while(top[p1]!=top[p2])
	{
		if(dep[top[p1]]<dep[top[p2]]) swap(p1,p2);
		ans.x=max(ans.x,t1.Query(1,1,dfc,dfn[top[p1]],dfn[p1],x));
		ans.y=max(ans.y,t2.Query(1,1,dfc,dfn[top[p1]],dfn[p1],x));
		p1=fa[top[p1]];
	}
	if(dep[p1]>dep[p2]) swap(p1,p2);
	ans.x=max(ans.x,t1.Query(1,1,dfc,dfn[p1],dfn[p2],x));
	ans.y=max(ans.y,t2.Query(1,1,dfc,dfn[p1],dfn[p2],x));
	return ans;
}

int main()
{
	int n,m,u,v;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf",&t1.pnt[i].x);
	for(int i=1;i<=n;i++) scanf("%lf",&t1.pnt[i].y);
	for(int i=1;i<=n;i++) scanf("%lf",&t2.pnt[i].x);
	for(int i=1;i<=n;i++) scanf("%lf",&t2.pnt[i].y);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	t1.Build(1,1,n);t2.Build(1,1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		double l=0,r=2e5,mid;
		while(r-l>eps)
		{
			mid=(l+r)/2;
			Point ans=Query(mid,u,v);
			if(dcmp(ans.x+ans.y)<=0) r=mid;
			else l=mid;
		}
		printf("%.3lf\n",l);
	}
	return 0;
}
