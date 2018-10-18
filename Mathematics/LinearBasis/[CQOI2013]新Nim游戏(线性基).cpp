#include<bits/stdc++.h>
using namespace std;

int a[110],base[35],n;

bool insert(int x)
{
	for(int i=30;i>=0;i--)
		if(x&(1<<i))
		{
			if(base[i]) x^=base[i];
			else{base[i]=x;break;}
		}
	return x==0;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+1+n);
	long long ans=0;
	for(int i=n;i>0;i--)
		if(insert(a[i])) ans+=1ll*a[i];
	cout<<ans<<endl;
	return 0;
}
