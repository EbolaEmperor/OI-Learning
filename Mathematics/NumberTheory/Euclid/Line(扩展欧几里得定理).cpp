#include<iostream>
#include<cstdio>
using namespace std;

long long ExGcd(long long a,long long b,long long &x,long long &y)  
{  
    if(!b)  
    {  
        x=1,y=0;  
        return a;  
    }  
    long long g=ExGcd(b,a%b,x,y);  
    long long t=x;  
    x=y;  
    y=t-(a/b)*y;  
    return g;  
}  //用于求解方程ax+by=GCD(a,b)

int main()
{
	long long a,b,c,gcd,x,y;
	cin>>a>>b>>c;
	gcd=ExGcd(a,b,x,y);
	if((-c)%gcd!=0) puts("-1");
	else printf("%lld %lld\n",x*(-c)/gcd,y*(-c)/gcd);
	return 0;
}
