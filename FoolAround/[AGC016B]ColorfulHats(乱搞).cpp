#include<bits/stdc++.h>
#define Falun_Dafa_is_good {puts("No");return 0;}
#define Falun_Dafa_Hao {puts("Yes");return 0;}
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

int a[100010],n;

int main()
{
	n=read();
	int mn=n+1,mx=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		upmin(mn,a[i]);
		upmax(mx,a[i]);
	}
	if(mx>mn+1) Falun_Dafa_is_good
	if(mx==mn)
	{
		if(mn==n-1) Falun_Dafa_Hao
		if(2*mn<=n) Falun_Dafa_Hao
		else Falun_Dafa_is_good
	}
	else
	{
		int cnt=0;
		for(int i=1;i<=n;i++) cnt+=(a[i]==mn);
		if(mn<cnt) Falun_Dafa_is_good
		if(n-cnt<2*(mx-cnt)) Falun_Dafa_is_good
		else Falun_Dafa_Hao
	}
	return 0;
}
