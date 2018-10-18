#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T,n,x;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&x),ans^=x;
		puts(ans?"Yes":"No");   //"Yes" means "First Win"
	}
	return 0;
}
