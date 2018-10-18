#include<iostream>
#include<cstdio>
using namespace std;

long long ExGcd(long long a,long long b,long long &x,long long &y)
{
	long long ret,tmp;
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	ret=ExGcd(b,a%b,x,y);
	tmp=x;
	x=y;
	y=tmp-a/b*y;
	return ret;
}

int main()
{
	long long x,y,m,n,l,x0=0,y0=0;
	cin>>x>>y>>m>>n>>l;
	if(m<n){long long t=m;m=n;n=t;t=x;x=y;y=t;}
	long long a=m-n,b=l,c=y-x;
	long long gcd=ExGcd(a,b,x0,y0);
	long long t=b/gcd;
	if(c%gcd!=0) puts("Impossible");
	else printf("%lld\n",(x0*(c/gcd)%t+t)%t);
	return 0;
}
