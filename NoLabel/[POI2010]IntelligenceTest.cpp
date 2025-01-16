#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}

const int A=1000010;
vector<int> p[A];

int main()
{
	int m=read(),x;
	for(int i=1;i<=m;i++)
	{
		x=read();
		p[x].push_back(i);
	}
	int n=read(),l;
	for(int i=1;i<=n;i++)
	{
		l=read();
		int now=0;
		bool flag=1;
		for(int j=1;j<=l;j++)
		{
			x=read();
			if(p[x].size()==0){flag=0;continue;}
			int tmp=upper_bound(p[x].begin(),p[x].end(),now)-p[x].begin();
			if(tmp>=p[x].size()) flag=0;
			else now=p[x][tmp];
		}
		puts(flag?"TAK":"NIE");
	}
	return 0;
}
