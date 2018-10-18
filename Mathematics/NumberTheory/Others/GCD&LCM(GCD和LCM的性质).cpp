#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	int T,gcd,lcm;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		scanf("%d%d",&gcd,&lcm);
		if(lcm%gcd!=0) printf("-1\n");
		else printf("%d %d\n",gcd,lcm);
	}
	return 0;
}
