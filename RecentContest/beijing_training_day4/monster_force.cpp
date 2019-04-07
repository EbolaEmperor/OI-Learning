#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=1010;
int a[N],b[N],n,k,q;

int getans()
{
	int mx=k,ans=1;
	for(int i=1;i<=n;i++)
	{
		ans=1ll*ans*min(a[i],mx)%ha;
		mx=max(mx,b[i]);
	}
	return ans;
}

int main()
{
	scanf("%d%d%d",&n,&q,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	printf("%d\n",getans());
	int opt,x,y;
	while(q--)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==0) a[x]=y;
		else b[x]=y;
		printf("%d\n",getans());
	}
	return 0;
}
