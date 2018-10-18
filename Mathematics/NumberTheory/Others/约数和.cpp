#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

long long work(long long x)
{
	long long ans=0,l=1,r;
	while(x/l!=0)
	{
		r=x/(x/l);
		ans+=((r-l+1)*(l+r)/2)*(x/l);
		l=r+1;
	}
	return ans;
}

int main()
{
	long long x,y;
	cin>>x>>y;
	cout<<work(y)-work(x-1)<<endl;
	system("pause");
	return 0;
}
