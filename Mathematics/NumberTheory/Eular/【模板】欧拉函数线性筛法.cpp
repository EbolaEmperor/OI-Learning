#include<bits/stdc++.h>
using namespace std;

int phi[1000010];
bool mark[1000010];
int prime[1000010],tot=0;

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
			if(i%prime[j]==0){phi[i*prime[j]]=phi[i]*prime[j];break;}
			else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

int main()
{
	int n;
	printf("n= ");
	cin>>n;
	getphi(n);
	for(int i=1;i<=n;i++) printf("phi[%d]=%d\n",i,phi[i]);
	return 0;
}
