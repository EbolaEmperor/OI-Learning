#include<iostream>
#include<cstdio>
using namespace std;

int a[30];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	int p=1;
	while(a[p]!=0) p++;
	if(p%2==0){puts("YES");return 0;}
	p=n;
	while(a[p]!=0) p--;
	if((n-p)%2==1) puts("YES");else puts("NO");
	return 0;
}
