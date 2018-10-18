#include<bits/stdc++.h>
using namespace std;

bool mark[50000];
int prime[50000],tot=0;
int phi[50000];

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
	if(n==1) {puts("0");return 0;}
	getphi(n);
	int ans=0;
	for(int i=1;i<n;i++) ans+=phi[i];
	cout<<(2*ans+1)<<endl;
	return 0;
}
