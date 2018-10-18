#include<iostream>
#include<cstdio>
using namespace std;

typedef long long LL;

LL Gcd(LL a,LL b){return b==0?a:Gcd(b,a%b);}

int main()
{
	LL m,n;
	cin>>m>>n;
	m++;n++;
	LL ans=(n*m)*(n*m-1)*(n*m-2)/6;
	if(n>=3) ans-=n*(n-1)*(n-2)/6*m;
	if(m>=3) ans-=m*(m-1)*(m-2)/6*n;
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
			ans-=(n-i)*(m-j)*(Gcd(i,j)-1)*2;
	cout<<ans<<endl;
	return 0;
}
