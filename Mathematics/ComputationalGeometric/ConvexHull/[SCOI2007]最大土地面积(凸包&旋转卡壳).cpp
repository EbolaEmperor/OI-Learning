#include<bits/stdc++.h>
using namespace std;

const int N=2010;
struct PNT
{
	double x,y;
	PNT(double a=0,double b=0):
		x(a),y(b){}
} pnt[N],ch[N];
int k;

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

int ConvexHull(int n)
{
	sort(pnt+1,pnt+1+n);
	int top=0;
	for(int i=1;i<=n;i++)
	{
		while(top>1&&dcmp(Cross(ch[top-1]-ch[top-2],pnt[i]-ch[top-2]))<=0) top--;
		ch[top++]=pnt[i];
	}
	k=top;
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
	int i=0,j=k-1;
	double ans=0;
	while(i<k||j<n)
	{
		int p1=i+1,p2=j+1;
		while(p1<j)
		{
			double tmp=fabs(Cross(ch[p1]-ch[i],ch[j]-ch[i]));
			tmp+=fabs(Cross(ch[j]-ch[i],ch[p2]-ch[i]));
			ans=max(ans,tmp/2);
			if(dcmp(Cross(ch[p1+1]-ch[p1],ch[p2+1]-ch[p2]))>=0) p2++;
			else p1++;
			if(p2>n) break;
		}
		if(dcmp(Cross(ch[i+1]-ch[i],ch[j+1]-ch[j]))>=0) j++;
		else i++;
		if(j>n) break;
	}
	return ans;
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
	printf("%.3lf\n",RevolvingShell(m));
	return 0;
}
