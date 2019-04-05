#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("data.in","w",stdout);
	srand(time(0));
	int n=4;
	printf("%d %d\n",n,n);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%100+1);puts("");
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%100+1);puts("");
	return 0;
}
