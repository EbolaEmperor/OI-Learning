#include<bits/stdc++.h>
using namespace std;

const int N=5000010;
int h[N],nxt[N],ch[N],to[N];
int tot=1,cnt[N],ans=0,etot=0;
char s[N];

void insert()
{
	int p=1,l=strlen(s);
	for(int i=0;i<l;i++)
	{
		int tmp,j=s[i];
		for(tmp=h[p];tmp;tmp=nxt[tmp])
			if(ch[tmp]==j) break;
		if(ch[tmp]!=j)
		{
			ch[++etot]=j;
			to[etot]=++tot;
			nxt[etot]=h[p];
			h[p]=etot;
			p=to[etot];
		}
		else p=to[tmp];
		cnt[p]++;
		ans=max(ans,cnt[p]*(i+1));
	}
}

int main()
{
	int n;scanf("%d",&n);
	while(gets(s))
	{
		if(strlen(s)==0) continue;
		if(s[0]=='\n') continue;
		insert();
	}
	cout<<ans<<endl;
	return 0;
}
