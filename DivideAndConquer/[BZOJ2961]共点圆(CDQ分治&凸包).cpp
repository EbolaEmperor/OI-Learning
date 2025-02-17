#include<bits/stdc++.h>
#define INF 1e40
using namespace std;

const int N=500010;
struct PNT
{
	double x,y;
	PNT(double a=0,double b=0):x(a),y(b){}
} pnt[N];
struct OPT
{
	int ty,id;double x,y;
	OPT(int a=0,double b=0,double c=0,int d=0):
		ty(a),x(b),y(c),id(d){}
} opt[N];
bool ans[N];

const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

bool operator < (const PNT &a,const PNT &b){return dcmp(a.x-b.x)<0||dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)<0;}
PNT operator - (const PNT &a,const PNT &b){return PNT(a.x-b.x,a.y-b.y);}
double Cross(const PNT &a,const PNT &b){return a.x*b.y-a.y*b.x;}
double Dot(const PNT &a,const PNT &b){return a.x*b.x+a.y*b.y;}

vector<PNT> up,down;int tp1=0,tp2=0;

bool solve(vector<PNT> &a,PNT p)
{
	int l=0,r=a.size()-1;
	while(r-l>2)
	{
		int mid1=(2*l+r)/3,mid2=(l+2*r)/3;
		if(dcmp(Dot(a[mid1],p)-Dot(a[mid2],p))<0) r=mid2;
		else l=mid1;
	}
	double ans=INF;
	for(int i=l;i<=r;i++)
		ans=min(ans,Dot(a[i],p));
	return dcmp(2*ans-Dot(p,p))>=0;
}

void CDQ(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2,cc=0;
	for(int i=L;i<=M;i++)
		if(opt[i].ty==0) pnt[++cc]=PNT(opt[i].x,opt[i].y);
	if(cc) sort(pnt+1,pnt+1+cc);
	tp1=tp2=0;up.clear();down.clear();
	for(int i=1;i<=cc;i++)
	{
		while(tp1>1&&dcmp(Cross(up[tp1-1]-up[tp1-2],pnt[i]-up[tp1-2]))>=0)up.pop_back(),tp1--;
		while(tp2>1&&dcmp(Cross(down[tp2-1]-down[tp2-2],pnt[i]-down[tp2-2]))<=0)down.pop_back(),tp2--;
		up.push_back(pnt[i]);tp1++;down.push_back(pnt[i]);tp2++;
	}
	for(int p=M+1;p<=R;p++)
		if(opt[p].ty==1&&ans[opt[p].id])
			if(dcmp(opt[p].y)>0) ans[opt[p].id]=solve(down,PNT(opt[p].x,opt[p].y));
			else ans[opt[p].id]=solve(up,PNT(opt[p].x,opt[p].y));
	CDQ(L,M);CDQ(M+1,R);
}

int main()
{
	int n,op,cnt=0,pos=-1;
	double x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%lf%lf",&op,&x,&y);
		if(op==1) ans[++cnt]=1;
		else if(pos==-1) pos=cnt;
		opt[i]=OPT(op,x,y,cnt);
	}
	CDQ(1,n);
	for(int i=1;i<=cnt;i++)
		puts((ans[i]&&i>pos)?"Yes":"No");
	return 0;
}
