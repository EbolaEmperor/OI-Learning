#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int inc=6000;
int a[1010],b[1010];
int f[1010][15000];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d%d",a+i,b+i);
	for(int j=0;j<1010;j++)
		for(int i=0;i<15000;i++)
			f[j][i]=10000;
	f[0][inc]=0;
	for(int i=1;i<=n;i++)
		for(int j=inc-5000;j<=inc+5000;j++)
			f[i][j]=min(f[i-1][j-(a[i]-b[i])],f[i-1][j-(b[i]-a[i])]+1);
	for(int i=0;i<=5000;i++)
	{
		int s=min(f[n][inc-i],f[n][inc+i]);
		if(s<10000){cout<<s<<endl;break;}
	}
	return 0;
}
