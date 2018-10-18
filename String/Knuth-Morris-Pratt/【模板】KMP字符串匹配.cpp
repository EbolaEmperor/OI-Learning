#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

string n,m;
int next[1000005];

void getnext(string p,int next_p[])
{
	int len_p=p.size(),k=-1,j=0;
	next_p[0]=-1;
	while(j<len_p)
		if(k==-1||p[j]==p[k])
			k++,j++,next_p[j]=k;
		else k=next_p[k];
}

int kmpsearch(string s,string p)
{
	int i=0,j=0;
	while(i<s.size()&&j<p.size())
		if(j==0||s[i]==p[j]) i++,j++;
		else j=next[j];
	if(j==p.size()) return i-j;
	else return -1;
}

int main()
{
	cin>>n>>m;
	getnext(m,next);
	int cnt=0,pos=0;
	next[0]=0;
	while(n.size()>0&&pos!=-1)
	{
		pos=kmpsearch(n,m);
		if(pos!=-1)
		{
			printf("%d\n",cnt+pos+1);
			cnt+=pos+1;
			n.erase(0,pos+1);
		}
	}
	for(int i=1;i<=m.size();i++) printf("%d ",next[i]);
	return 0;
}
