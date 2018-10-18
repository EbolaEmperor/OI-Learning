#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
char s[N];
int sa[N],rk[N],c[N];
int x[N],y[N],tmp[N];
int height[N];

void getSA(int n,int m)
{
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i+1]+=c[i];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
		for(int i=1;i<=n;i++) c[tmp[i]]++;
		for(int i=1;i<m;i++) c[i+1]+=c[i];
		for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
		num=1;swap(x,y);x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
}

void getHeight(int n)
{
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]==1) continue;   //height[1]=0
		if(k) k--;   //h[i]>=h[i-1]-1
		int j=sa[rk[i]-1];
		while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;   //h[i]=height[rk[i]]
	}
}

int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	getSA(n,131);getHeight(n);
	for(int i=1;i<=n;i++) printf("%d ",sa[i]);puts("");
	for(int i=1;i<=n;i++) printf("%d ",rk[i]);puts("");
	for(int i=1;i<=n;i++) printf("%d ",height[i]);
	return 0;
}
