#include<bits/stdc++.h>
using namespace std;

const int N=60010;
int s[N];
int sa[N],Rank[N];
int x[N],y[N],c[N],tmp[N];

int readc()
{
	char ch=getchar();
	while(ch<'A'||ch>'Z') ch=getchar();
	return ch-'A'+1;
}

void get_sa(int n,int m)
{
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i+1]+=c[i];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k*=2)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
		for(int i=1;i<=n;i++) c[tmp[i]]++;
		for(int i=1;i<m;i++) c[i+1]+=c[i];
		for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
		swap(x,y);
		x[sa[1]]=1;num=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) Rank[sa[i]]=i;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		s[i]=readc();
	s[n+1]=27;
	for(int i=n+2;i<=2*n+1;i++)
		s[i]=s[2*(n+1)-i];
	get_sa(2*n+1,27);
	int p1=1,p2=n+2,cnt=0;
	while(p1+p2<=2*n+2)
	{
		if(Rank[p1]<Rank[p2]) putchar(s[p1++]+'A'-1);
		else putchar(s[p2++]+'A'-1);
		if(++cnt%80==0) putchar('\n');
	}
	return 0;
}
