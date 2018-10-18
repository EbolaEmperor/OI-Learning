#include<bits/stdc++.h>
using namespace std;

int fa[300010][20];
int w[300010][20];

int main()
{
	int n,s,a,b;
	cin>>n>>s;
	for(int i=1;i<=n;i++) scanf("%d",&w[i][0]);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		fa[b][0]=a;
	}
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
			w[i][j]=w[i][j-1]+w[fa[i][j-1]][j-1];
		}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int p=i,x=s;
		for(int j=17;j>=0;j--)
			if(w[p][j]<=x) x-=w[p][j],p=fa[p][j];
		if(x==0) ans++;
	}
	cout<<ans<<endl;
}
