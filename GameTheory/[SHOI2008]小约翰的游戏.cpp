#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T,n,x;
	for(scanf("%d",&T);T;T--)
	{
		bool f=1;int s=0;
		for(scanf("%d",&n);n;n--)
		{
			scanf("%d",&x);
			s^=x;
			if(x!=1) f=0;
		}
		puts((!f&&s)||(!s&&f)?"John":"Brother");
	}
	return 0;
}
