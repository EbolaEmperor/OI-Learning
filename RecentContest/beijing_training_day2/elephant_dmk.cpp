#include<bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(0));
	int m=5,n=10,q=2;
	printf("0\n%d %d %d\n",m,n,q);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%5+1);puts("");
	for(int i=1;i<=1;i++)
	{
		int l=rand()%n+1,r=rand()%n+1;
		if(l>r) swap(l,r);
		printf("2 %d %d\n",l,r);
	}
	int l=rand()%n+1,r=rand()%n+1;
	if(l>r) swap(l,r);
	printf("1 %d %d\n",l,r);
	return 0;
}
