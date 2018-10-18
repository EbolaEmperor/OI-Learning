#include<bits/stdc++.h>
using namespace std;

const int MAXN=2000010;
int ch[MAXN][26],prt[MAXN];
int len[MAXN],cnt[MAXN];
int lst=1,tot=1;
int c[MAXN],a[MAXN];
char s[MAXN],qs[2*MAXN];
int tag[MAXN];

void insert(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;
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
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;cnt[lst]=1;
}

int main()
{
	scanf("%s",s);
	int l=strlen(s);
	for(int i=0;i<l;i++)
		insert(s[i]-'a');
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<=tot;i++) c[i]+=c[i-1];
	for(int i=1;i<=tot;i++) a[c[len[i]]--]=i;
	for(int i=tot;i>=1;i--) cnt[prt[a[i]]]+=cnt[a[i]];
	int q;scanf("%d",&q);
	for(int Q=1;Q<=q;Q++)
	{
		scanf("%s",qs);
		int lq=strlen(qs),n=2*lq,p=1,g=0,ans=0;
		for(int i=lq;i<n;i++) qs[i]=qs[i-lq];
		for(int i=0;i<n;i++)
		{
			int c=qs[i]-'a';
			if(ch[p][c]) p=ch[p][c],g++;
			else
			{
				while(p&&!ch[p][c]) p=prt[p];
				if(!p) p=1,g=0;
				else g=len[p]+1,p=ch[p][c];
			}
			if(g>=lq)
			{
				while(prt[p]&&len[prt[p]]>=lq) p=prt[p],g=len[p];
				if(tag[p]!=Q) tag[p]=Q,ans+=cnt[p];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
