#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

vector<LL> ans;

LL Init(LL n)     //make n to an odd integer
{
	while(n%2==0) n/=2,ans.push_back(2);
	return n;
}

pair<LL,LL> Fermat(LL n)     //n is an odd integer
{
	LL a=(LL)ceil(sqrt(n));
	LL b2=a*a-n;
	while((LL)ceil(sqrt(b2))*(LL)ceil(sqrt(b2))!=b2)
	{
		a++;
		b2=a*a-n;
	}
	return make_pair(a-(LL)sqrt(b2),a+(LL)sqrt(b2));
}

void work(LL n)
{
	pair<LL,LL> x=Fermat(n);
	if(x.first==1&&x.second==1) return;
	else if(x.first==1) ans.push_back(x.second);
	else if(x.second==1) ans.push_back(x.first);
	else work(x.first),work(x.second);
}

int main()
{
	printf("Input an integer:  ");
	LL n;
	cin>>n;
	printf("%lld",n);
	if(n%2==0)
	{
		n=Init(n);
		work(n);
	}
	else work(n);
	sort(ans.begin(),ans.end());
	printf(" = %lld",ans[0]);
	for(int i=1;i<(int)ans.size();i++) printf(" * %lld",ans[i]);
	putchar('\n');
	return 0;
}
