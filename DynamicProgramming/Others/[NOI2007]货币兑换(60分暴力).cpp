#include<bits/stdc++.h>
using namespace std;

const int N=100010;
double a[N],b[N],rate[N];
double f[N];

int main()
{
	int n;double s;
	scanf("%d%lf",&n,&s);
	double ans=s;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",a+i,b+i,rate+i);
		for(int j=1;j<i;j++)
			ans=max(ans,f[j]*b[i]+f[j]*rate[j]*a[i]);
		f[i]=ans/(a[i]*rate[i]+b[i]);
	}
	printf("%.3lf\n",ans);
	return 0;
}
