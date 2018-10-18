#include<bits/stdc++.h>
using namespace std;

const int N=10010;
double s[N],k[N],v[N],E;
int n;

double gao(double x,int p)
{
	double l=max(v[p],0.0),r=1e5,mid;
	for(int cnt=60;cnt;cnt--)
	{
		mid=(l+r)/2;
		if(2*k[p]*x*mid*mid*(mid-v[p])+s[p]>0) l=mid;
		else r=mid;
	}
	return r;
}

int main()
{
	scanf("%d%lf",&n,&E);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",s+i,k+i,v+i);
	for(int i=1;i<=n;i++) k[i]*=s[i];
	double l=-1e5,r=0,mid;
	for(int cnt=70;cnt;cnt--)
	{
		mid=(l+r)/2;
		double res=0;
		for(int i=1;i<=n;i++)
		{
			double y=gao(mid,i);
			res+=k[i]*(y-v[i])*(y-v[i]);
		}
		if(res<=E) l=mid;
		else r=mid;
	}
	double ans=0;
	for(int i=1;i<=n;i++)
		ans+=s[i]/gao(r,i);
	printf("%.8lf\n",ans);
	return 0;
}
