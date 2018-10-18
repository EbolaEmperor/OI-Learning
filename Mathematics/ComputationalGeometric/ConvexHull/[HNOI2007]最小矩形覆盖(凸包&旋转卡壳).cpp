#include<bits/stdc++.h>
using namespace std;

const int N=50010;
struct PNT
{
	double x,y;
	PNT(double a=0,double b=0):x(a),y(b){}
} pnt[N],ch[N],ans[10];

const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

bool operator < (const PNT &a,const PNT &b){return dcmp(a.x-b.x)<0||dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)<0;}
PNT operator - (const PNT &a,const PNT &b){return PNT(a.x-b.x,a.y-b.y);}
PNT operator + (const PNT &a,const PNT &b){return PNT(a.x+b.x,a.y+b.y);}
PNT operator - (const PNT &a){return PNT(-a.x,-a.y);}
PNT operator * (const PNT &a,const double &x){return PNT(a.x*x,a.y*x);}
PNT operator / (const PNT &a,const double &x){return PNT(a.x/x,a.y/x);}
double Cross(const PNT &a,const PNT &b){return a.x*b.y-a.y*b.x;}
double Dot(const PNT &a,const PNT &b){return a.x*b.x+a.y*b.y;}

int ConvexHull(int n)
{
	sort(pnt+1,pnt+1+n);
	int top=0;
	for(int i=1;i<=n;i++)
	{
		while(top>1&&dcmp(Cross(ch[top-1]-ch[top-2],pnt[i]-ch[top-2]))<=0) top--;
		ch[top++]=pnt[i];
	}
	int k=top;
	for(int i=n-1;i>=1;i--)
	{
		while(top>k&&dcmp(Cross(ch[top-1]-ch[top-2],pnt[i]-ch[top-2]))<=0) top--;
		ch[top++]=pnt[i];
	}
	if(n>1) top--;
	return top;
}

double RevolvingShell(int n)
{
	int l=1,r=1,p=1;PNT v;
	double mn=1e40;
	for(int i=0;i<n;i++)
	{
		v=ch[i+1]-ch[i];
		while(dcmp(Cross(v,ch[p+1]-ch[p]))>=0) p=(p+1)%n;
		while(dcmp(Dot(v,ch[r+1]-ch[r]))>=0) r=(r+1)%n;
		while(dcmp(Cross(v,ch[l+1]-ch[l]))>=0||dcmp(Dot(v,ch[l+1]-ch[l]))<0) l=(l+1)%n;
		PNT A=ch[i]+v*Dot(v,ch[r]-ch[i])/Dot(v,v);
		PNT B=ch[i]+(-v)*Dot(-v,ch[l]-ch[i])/Dot(v,v);
		PNT C=ch[p]+v*Dot(v,ch[r]-ch[p])/Dot(v,v);
		if(dcmp(fabs(Cross(B-A,C-A))-mn)<=0)
		{
			mn=fabs(Cross(B-A,C-A));
			ans[0]=B;ans[1]=A;ans[2]=C;
			ans[3]=C+(B-A);
		}
	}
	return mn;
}

int main()
{
	int n;
	double x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&x,&y);
		pnt[i]=PNT(x,y);
	}
	int m=ConvexHull(n);
	double area=RevolvingShell(m);
	printf("%.5lf\n",area);
	for(int i=0;i<4;i++)
	{
		if(dcmp(ans[i].x)==0) ans[i].x=0;
		if(dcmp(ans[i].y)==0) ans[i].y=0;
	}
	x=ans[0].x;y=ans[0].y;int pp=0;
	for(int i=1;i<4;i++)
		if(dcmp(ans[i].y-y)<0||dcmp(ans[i].y-y)==0&&dcmp(ans[i].x-x)<0)
			x=ans[i].x,y=ans[i].y,pp=i;
	for(int i=pp;i<pp+4;i++)
		printf("%.5lf %.5lf\n",ans[i%4].x,ans[i%4].y);
	return 0;
}
