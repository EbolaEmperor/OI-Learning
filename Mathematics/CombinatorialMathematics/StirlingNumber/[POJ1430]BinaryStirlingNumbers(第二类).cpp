#include<bits/stdc++.h>
using namespace std;

int div(int n)
{
	int cnt=0,b=2;
	while(n/b) cnt+=n/b,b*=2;
	return cnt;
}

int main()
{
	int T,n,k;
	for(cin>>T;T;T--)
	{
		scanf("%d%d",&n,&k);
		int z=n-(k+2)/2,w=(k-1)/2;
		puts((div(z)-div(w)-div(z-w)>0)?"0":"1");
	}
	return 0;
}
