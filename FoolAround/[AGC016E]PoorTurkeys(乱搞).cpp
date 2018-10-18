#include<bits/stdc++.h>
using namespace std;

const int M=100010;
bool stu[410][410];
int n,m,a[M],b[M];
bool cant[410];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",a+i,b+i);
	for(int i=1;i<=n;i++)
	{
		stu[i][i]=1;
		for(int j=m;j>=1;j--)
		{
			bool x=stu[i][a[j]],y=stu[i][b[j]];
			if(x&&y){cant[i]=1;break;}
			else if(x) stu[i][b[j]]=1;
			else if(y) stu[i][a[j]]=1;
		}
	}
	int ans=0;
	for(int i=1;i<n;i++)
	{
		if(cant[i]) continue;
		for(int j=i+1;j<=n;j++)
		{
			if(cant[j]) continue;
			bool flag=1;
			for(int k=1;k<=n;k++)
				if(stu[i][k]&&stu[j][k]) flag=0;
			ans+=flag;
		}
	}
	printf("%d\n",ans);
	return 0;
}
