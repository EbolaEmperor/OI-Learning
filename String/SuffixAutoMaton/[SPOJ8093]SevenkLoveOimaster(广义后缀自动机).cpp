#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int ch[N][26],prt[N];
int len[N],cnt[N];
int tag[N];
int lst=1,tot=1;
char s[N];

void insert(int c,int k)
{
	int p=lst,np=++tot;
	len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			tag[nq]=tag[q];cnt[nq]=cnt[q];
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
	while(np)
	{
		if(tag[np]!=k)
			tag[np]=k,
			cnt[np]++;
		np=prt[np];
	}
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		int l=strlen(s);lst=1;
		for(int j=0;j<l;j++)
			insert(s[j]-'a',i);
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%s",s);
		int p=1,l=strlen(s);
		for(int j=0;j<l;j++)
		{
			if(!ch[p][s[j]-'a']){puts("0");break;}
			p=ch[p][s[j]-'a'];
			if(j+1==l) printf("%d\n",cnt[p]);
		}
	}
	return 0;
}
