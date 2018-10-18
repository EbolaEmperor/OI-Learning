#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	int a=0,b=0x7fffffff,cnt;
	string s;
	for(int i=1;i<=8;i++)
	{
		cin>>s;
		cnt=0;
		for(int j=0;j<s.size();j++)
			if(s[j]=='B') cnt++;
		if(cnt==8) a++;
		b=min(b,cnt);
	}
	int ans=a+b;
	if(a==8) ans=8;
	cout<<ans<<endl;
	return 0;
}
