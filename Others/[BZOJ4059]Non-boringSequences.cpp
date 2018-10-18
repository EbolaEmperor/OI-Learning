#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=200010;
map<int,int> now;
int pre[N],nxt[N],a[N];

bool chk(int L,int R)
{
	if(L>=R) return 1;
	int p1=L,p2=R;
	while(p1<=p2)
	{
		if(pre[p1]<L&&nxt[p1]>R) return chk(L,p1-1)&&chk(p1+1,R);p1++;
		if(pre[p2]<L&&nxt[p2]>R) return chk(L,p2-1)&&chk(p2+1,R);p2--;
	}
	return 0;
}

int main()
{
	for(int T=read();T;T--)
	{
		int n=read();
		now.clear();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();int t=now[a[i]];
			nxt[t]=i;pre[i]=t;now[a[i]]=i;
		}
		for(int i=1;i<=n;i++) nxt[now[a[i]]]=n+1;
		puts(chk(1,n)?"non-boring":"boring");
	}
	return 0;
}
