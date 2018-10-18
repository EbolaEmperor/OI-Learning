#include<bits/stdc++.h>
#define ha 100003
using namespace std;

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

const int N=100010;
bool chs[N],a[N];
int n,k,facn=1;
int g[N];

int Init()
{
	int dafa=0;
	for(int i=n;i>=1;i--)
	{
		facn=1ll*i*facn%ha;
		bool falun=a[i];
		for(int j=i+i;j<=n;j+=i)
			if(chs[j]) falun^=1;
		if(falun) chs[i]=1,dafa++;
	}
	if(dafa<=k) printf("%d\n",1ll*dafa*facn%ha),exit(0);
	return dafa;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	int cnt=Init();g[n]=1;
	for(int i=n-1;i>k;i--)
		g[i]=(1ll*(n-i)*g[i+1]%ha+n)*Pow(i,ha-2)%ha;
	int ans=k;
	for(int i=k+1;i<=cnt;i++) ans=(ans+g[i])%ha;
	printf("%d\n",1ll*ans*facn%ha);
	return 0;
}
