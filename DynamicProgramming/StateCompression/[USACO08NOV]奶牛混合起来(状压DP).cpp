#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define fuck(x,y) (x&(1<<y))
using namespace std;

long long f[1<<18][20];
int a[20];

int main()
{
	int n,s;
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		f[1<<i][i]=1;
	}
	for(int i=0;i<=((1<<n)-1);i++)
		for(int j=0;j<n;j++)
			if(fuck(i,j))
				for(int k=0;k<n;k++)
					if(!fuck(i,k)&&abs(a[j]-a[k])>s) f[i|(1<<k)][k]+=f[i][j];
	long long ans=0;
	for(int i=0;i<n;i++) ans+=f[(1<<n)-1][i];
	cout<<ans<<endl;
	return 0;
}
