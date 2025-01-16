#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
using namespace std;

map<string,int> m;
string s[1005],name[1005];
int p[1005];

int main()
{
	int n,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]>>p[i];
		if(!m.count(s[i])) name[++cnt]=s[i];
		m[s[i]]+=p[i];
	}
	int max=0,maxn=0;
	string maxs;
	vector<string> winner;
	for(int i=1;i<=cnt;i++)
		if(m[name[i]]>max)
		{
			max=m[name[i]];
			winner.clear();
			winner.push_back(name[i]);
			maxn=1;
		}
		else if(m[name[i]]==max) maxn++,winner.push_back(name[i]);
	if(maxn>1)
	{
		m.clear();
		for(int i=1;i<=n;i++)
			for(int j=0;j<winner.size();j++)
				if(s[i]==winner[j])
				{
					m[s[i]]+=p[i];
					if(m[s[i]]>=max){cout<<s[i]<<endl;return 0;}
				}
	}
	else cout<<winner[0]<<endl;
	return 0;
}
