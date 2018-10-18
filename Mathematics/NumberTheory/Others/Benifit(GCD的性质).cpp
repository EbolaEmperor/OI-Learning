#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int a,c;
		scanf("%d%d",&a,&c);
		if(c%a!=0){puts("NO SOLUTION");continue;}
		int b=c/a,g=__gcd(a,b);
		while(g!=1)
		{
			a/=g;
			b*=g;
			g=__gcd(a,b);
		}
		printf("%d\n",b);
	}
	return 0;
}
