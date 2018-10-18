#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

int main()
{
	string s1,s2;
	int n,ans=0;
	cin>>n>>s1>>s2;
	for(int i=0;i<s1.size();i++)
	{
		int x=abs(s2[i]-s1[i]);
		ans+=min(x,10-x);
	}
	cout<<ans<<endl;
	return 0;
}
