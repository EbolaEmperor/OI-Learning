#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	int T;
	for(cin>>T;T;T--)
	{
		int m,n;
		scanf("%d%d",&m,&n);
		bool sg=1;
		if(n>m) swap(m,n);
		while(m/n==1&&m%n!=0)
		{
			int tmp=n;
			n=m%n;
			m=tmp;
			sg=!sg;
		}
		if(sg) puts("Stan wins");else puts("Ollie wins");
	}
	return 0;
}
