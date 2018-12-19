#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

int f1[1010],f2[1010];
int hs[110],vs[110],ss=0;
int hb[110],vb[110],sb=0;

int main()
{
	int n,t,k,x,y;
	cin>>n>>t>>k;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		if(y>=k) hb[++sb]=y,vb[sb]=x;
		else hs[++ss]=y,vs[ss]=x;
	}
	for(int i=0;i<=t;i++) f1[i]=f2[i]=-INF;
	for(int i=1;i<=sb;i++) f2[hb[i]]=max(f2[hb[i]],vb[i]);
	for(int i=1;i<=sb;i++)
	{
		int h=hb[i]/5*4;
		for(int j=0;j<=t-h;j++) f2[j+h]=max(f2[j+h],f2[j]+vb[i]);
	}
	f1[0]=0;
	for(int i=1;i<=ss;i++)
	{
		int h=hs[i]/5*4;
		for(int j=0;j<=t-h;j++) f2[j+h]=max(f2[j+h],f2[j]+vs[i]);
		for(int j=0;j<=t-hs[i];j++) f1[j+hs[i]]=max(f1[j+hs[i]],f1[j]+vs[i]);
	}
	int ans=0;
	for(int i=0;i<=t;i++) ans=max(ans,max(f1[i],f2[i]));
	cout<<ans<<endl;
	return 0;
}
