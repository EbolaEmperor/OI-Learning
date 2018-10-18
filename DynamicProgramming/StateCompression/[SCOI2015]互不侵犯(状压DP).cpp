#include<iostream>
#include<cstdio>
using namespace std;

long long f[10][4096][85];     //第i行，状态j，已放k个国王的方案数
int cnt[4096];     //状态中含有几个国王

int fuck(int a,int b){return (a&b)|(a&(b>>1))|(a&(b<<1));}
int fuck(int a){return a&(a>>1);}

void BitOut(int a)
{
	int s[50],cnt=0;
	while(a)
	{
		s[++cnt]=a%2;
		a/=2;
	}
	for(int i=cnt;i>=1;i--) putchar(s[i]+48);
	if(cnt==0) putchar(48);
	puts("");
}

int main()
{
	int n,m;
	cin>>n>>m;
	int MAX=(1<<n)-1;
	for(int i=0;i<=MAX;i++)
	{
		int x=i;
		while(x)
		{
			if(x%2==1) cnt[i]++;
			x>>=1;
		}
	}
	f[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=MAX;j++)
			if(!fuck(j))
				for(int k=0;k<=MAX;k++)
					if(!fuck(k)&&!fuck(j,k))
					{
						//BitOut(j);BitOut(k);
						for(int l=cnt[j];l<=m;l++)
							f[i][j][l]+=f[i-1][k][l-cnt[j]];
					}
	long long ans=0;
	for(int i=0;i<=MAX;i++)
		if(!fuck(i)) ans+=f[n][i][m];
	cout<<ans<<endl;
	return 0;
}
