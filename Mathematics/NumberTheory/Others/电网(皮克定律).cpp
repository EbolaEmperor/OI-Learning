#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int gcd(int x,int y)
{
	if(x>y) swap(x,y);
	if(x==0) return y;
	return gcd(y%x,x);
}

int main()
{
	int n,m,p,b=0,s;
	cin>>n>>m>>p;
	s=p*m/2;
	b+=gcd(n,m);
	if(p==n) b+=m;
	else b+=gcd(abs(p-n),m);
	b+=p;
	cout<<s+1-b/2<<endl;
	return 0;
}
