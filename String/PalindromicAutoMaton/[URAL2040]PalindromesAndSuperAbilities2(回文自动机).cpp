#include<bits/stdc++.h>
using namespace std;

const int MAXN=5000010;
char ss[MAXN];
int s[MAXN],n;
int ch[MAXN][2],sz;
int fail[MAXN],lst;
int len[MAXN];

int newnode(int l){len[++sz]=l;return sz;}

void init()
{
	sz=-1;
	n=lst=0;
	newnode(0);
	newnode(-1);
	fail[0]=1;
	s[0]=-1;
}

int find(int p)
{
	while(s[n]!=s[n-len[p]-1]) p=fail[p];
	return p;
}

bool insert(int c)
{
	bool flag=0;
	s[++n]=c;
	int cur=find(lst);
	if(!ch[cur][c])
	{
		flag=1;
		int now=newnode(len[cur]+2);
		fail[now]=ch[find(fail[cur])][c];
		ch[cur][c]=now;
	}
	lst=ch[cur][c];
	return flag;
}

int main()
{
	scanf("%s",ss);
	init();
	int l=strlen(ss);
	for(int i=0;i<l;i++)
		printf("%d",insert(ss[i]-'a'));
	return 0;
}
