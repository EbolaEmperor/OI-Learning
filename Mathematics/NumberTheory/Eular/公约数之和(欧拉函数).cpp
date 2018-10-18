#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int phi[2000010];
int prime[2000010],tot=0;
bool mark[2000010];

void getphi(int n)
{
	memset(mark,0,sizeof(mark));
	phi[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!mark[i])
		{
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=tot&&i*prime[j]<=n;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j];
			else phi[i*prime[j]]=phi[i]*(prime[j]-1);	
		}
	}
}

int main()
{
	int n;
	cin>>n;
	getphi(n);
	long long ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i*2;j<=n;j+=i)
			ans+=(long long)i*phi[j/i];
	cout<<ans<<endl;
	return 0;
}
