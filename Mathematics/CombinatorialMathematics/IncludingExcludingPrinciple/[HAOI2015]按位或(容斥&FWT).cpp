#include<bits/stdc++.h>
using namespace std;

void FWT(double *a,int n)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0;k<i;k++)
				a[i+j+k]+=a[j+k];
}

const int N=1048590;
const double eps=1e-9;
double p[N],f[N];
int cnt[N];

double inv(double x){return fabs(x)<eps?0:1/x;}

int main()
{
	int k;
	scanf("%d",&k);
	int n=1<<k,t=0;
	for(int i=0;i<n;i++)
	{
		scanf("%lf",p+i);
		if(fabs(p[i])>eps) t|=i;
	}
	if(t!=n-1){puts("INF");return 0;}
	for(int i=0;i<=n;i++)
		cnt[i]=cnt[i>>1]+(i&1);
	FWT(p,n);
	for(int i=0;i<n;i++)
		f[i]=inv(1-p[(n-1)^i]);
	double ans=0;
	for(int i=0;i<n;i++)
		ans+=(cnt[i]&1?1:-1)*f[i];
	printf("%.9lf\n",ans);
	return 0;
}
