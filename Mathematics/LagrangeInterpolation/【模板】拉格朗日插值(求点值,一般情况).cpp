#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int lagrange(int *arrx,int *arry,int n,int x)
{
	int res=0;
	for(int i=0;i<n;i++)
	{
		int s1=1,s2=1;
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			s1=1ll*s1*(x-arrx[j])%ha;
			s2=1ll*s2*(arrx[i]-arrx[j])%ha;
		}
		res=(res+1ll*s1*Pow(s2,ha-2)%ha*arry[i])%ha;
	}
	return (res%ha+ha)%ha;
}

int a[2010],b[2010];

int main()
{
	int n,x;
	scanf("%d%d",&n,&x);
	for(int i=0;i<n;i++)
		scanf("%d%d",a+i,b+i);
	printf("%d\n",lagrange(a,b,n,x));
	return 0;
}
