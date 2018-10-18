#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("data.in","w",stdout);
	const int N=50000;
	for(int i=1;i<=N;i++)
		printf("1 %d\n",i);
	for(int i=1;i<=N;i++)
	{
		int f=rand()%2;
		printf("3 %d\n",(f&1)?1:N);
	}
	return 0;
}
