#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int n,m,a[N],b[N],posa,posb;
int wtl[N],wtc[N];

bool check(int x)
{
	long long sum=0; //独立集大小(先假设全选黑点)
	int j=m;
	for(int i=1;i<=n;i++)
	{
		while(j&&a[i]+b[j]>x)
			wtc[j]=i-1,j--;
		wtl[i]=j;
		sum+=m-wtl[i];
	}
	for(;j;j--) wtc[j]=n;
	long long s1=0,s2=0; //最大独立集大小(s2是不能包含初始点的) 
	for(int i=0,j=0;i<=n;i++)
	{
		sum+=min(wtl[i],j);
		s1=max(s1,sum);
		s2=max(s2,sum-(i<posa&&j<posb));
		while(j<m&&i+wtc[j+1]-n>=0)
		{
			j++;
			sum+=i+wtc[j]-n;
			s1=max(s1,sum);
			s2=max(s2,sum-(i<posa&&j<posb));
		}
		sum-=min(m-wtl[i+1],m-j);
	}
	return s1==s2;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=m;i++) scanf("%d",b+i);
	posa=a[1];posb=b[1];
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=n;i>=1;i--)
		if(a[i]==posa){posa=i;break;}
	for(int i=m;i>=1;i--)
		if(b[i]==posb){posb=i;break;}
	int l=2,r=a[posa]+b[posb],mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
