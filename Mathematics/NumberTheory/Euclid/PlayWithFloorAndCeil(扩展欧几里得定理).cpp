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
}  

int main()
{
	long long m,k,x,y;
	int T;
	for(cin>>T;T;T--)
	{
		scanf("%lld%lld",&m,&k);
		if(m%k==0) printf("0 %lld\n",k);
		else
		{
			ExGcd(m/k,m/k+1,x,y);
			printf("%lld %lld\n",x*m,y*m);
		}
	}
	return 0;
}
