#include<bits/stdc++.h>
using namespace std;

int mult[1500010][20];
int pw2[20],lg2[1500010];

int main()
{
	int n,m,l,r;
	cin>>n>>m;
	memset(mult,0,sizeof(mult));
	for(int i=1;i<=n;i++) scanf("%d",&mult[i][0]);
	pw2[0]=1;
	for(int i=1;i<=17;i++) pw2[i]=pw2[i-1]*2;
	int pos=0;
	for(int i=1;i<=n;i++)
	{
		if(i>=pw2[pos+1]) pos++;
		lg2[i]=pos;
	}
	for(int i=1;i<=17;i++)
		for(int j=1;j<=n;j++)
			mult[j][i]=max(mult[j][i-1],mult[j+pw2[i-1]][i-1]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		int p=lg2[r-l+1];
		printf("%d\n",max(mult[l][p],mult[r-pw2[p]+1][p]));
	}
	return 0;
}
