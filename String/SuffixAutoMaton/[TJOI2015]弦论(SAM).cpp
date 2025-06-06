#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
int ch[N][26],len[N],prt[N];
int tot=1,lst=1,size[N],cnt[N];
char s[N];
bool t;
int c[N],a[N];

void insert(int c)
{
	int p=lst,np=++tot;
	len[np]=len[p]+1;cnt[np]=1;
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
	lst=np;
}

void count()
{
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<=tot;i++) c[i]+=c[i-1];
	for(int i=1;i<=tot;i++) a[c[len[i]]--]=i;
	for(int i=tot;i>=1;i--)
		if(t) cnt[prt[a[i]]]+=cnt[a[i]];
		else cnt[a[i]]=1;
	cnt[1]=0;
	for(int i=tot;i>=1;i--)
	{
		int p=a[i];
		size[p]=cnt[p];
		for(int j=0;j<26;j++)
			if(ch[p][j]) size[p]+=size[ch[p][j]];
	}
}

int main()
{
	scanf("%s",s);
	int l=strlen(s),k;
	for(int i=0;i<l;i++) insert(s[i]-'a');
	scanf("%d%d",&t,&k);
	count();int p=1;
	if(k>size[1]){puts("-1");return 0;}
	while(k>0)
	{
		int c=0;
		while(k>=size[ch[p][c]]) k-=size[ch[p][c++]];
		p=ch[p][c];
		putchar(c+'a');
		k-=cnt[p];
	}
	return 0;
}
