#include<bits/stdc++.h>
using namespace std;

int a[110],c[110];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),c[a[i]]++;
	sort(a+1,a+n+1,greater<int>());
	int mid=(a[1]+1)/2,gg=(a[1]&1)+1;
	if(a[n]<mid||c[mid]!=gg) return puts("Impossible"),0;
	for(int i=a[1];i>mid;i--) if(c[i]<2) return puts("Impossible"),0;
	puts("Possible");
	return 0;
}
