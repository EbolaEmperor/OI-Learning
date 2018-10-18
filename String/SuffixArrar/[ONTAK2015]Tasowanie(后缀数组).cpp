#include<bits/stdc++.h>
using namespace std;

const int N=400010;
int s[N];
int sa[N],Rank[N];
int x[N],y[N],c[N],tmp[N];

void get_sa(int n,int m)
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
		swap(x,y);x[sa[1]]=1;num=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) Rank[sa[i]]=i;
}


int main()
{
	int l1,l2;
	scanf("%d",&l1);
	for(int i=1;i<=l1;i++) scanf("%d",s+i);
	s[l1+1]=1001;
	scanf("%d",&l2);
	s[l1+l2+2]=1001;
	for(int i=1;i<=l2;i++) scanf("%d",s+l1+1+i);
	get_sa(l1+l2+2,1001);
	int p1=1,p2=l1+2;
	while(p1<=l1||p2<=l1+l2+1)
		if((p1<=l1&&Rank[p1]<Rank[p2])||p2>l1+l2+1) printf("%d ",s[p1++]);
		else printf("%d ",s[p2++]);
	return 0;
}
