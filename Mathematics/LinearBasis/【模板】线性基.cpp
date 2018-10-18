#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL base[55];

int main()
{
	int n;
	cin>>n;
	memset(base,0,sizeof(base));
	for(int i=1;i<=n;i++)
	{
		LL x;
		cin>>x;
		for(LL j=50;j>=0;j--)
			if(x&(1ll<<j))
			{
				if(base[j]) x^=base[j];
				else{base[j]=x;break;}
			}
	}
	LL ans=0;
	for(int i=50;i>=0;i--)
		if((ans^base[i])>ans) ans^=base[i];
	cout<<ans<<endl;
	return 0;
}
