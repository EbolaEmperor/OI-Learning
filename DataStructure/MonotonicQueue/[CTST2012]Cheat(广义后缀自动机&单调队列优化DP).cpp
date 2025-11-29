#include<bits/stdc++.h>
using namespace std;

const int N=2500010;
int ch[N][2],prt[N],len[N];
int lst=1,tot=1;
char s[N];

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
	lst=np;
}

int v[N],f[N];

void match(int l)
{
	int p=1,x=0;
	for(int i=0;i<l;i++)
	{
		int c=s[i]-'0';
		if(ch[p][c]) p=ch[p][c],x++;
		else
		{
			while(p&&!ch[p][c]) p=prt[p];
			if(!p) x=0,p=1;
			else x=len[p]+1,p=ch[p][c];
		}
		v[i+1]=x;
	}
}

bool check(int x,int l)
{
	queue<int> q;f[0]=0;
	for(int i=1;i<=l;i++)
	{
		f[i]=f[i-1];
		int p=i-x;
		if(p>=0)
		{
			while(!q.empty()&&f[p]-p>f[q.front()]-q.front()) q.pop();
			q.push(p);
		}
		while(!q.empty()&&q.front()<i-v[i]) q.pop();
		if(!q.empty()) f[i]=max(f[i],f[q.front()]+i-q.front());
	}
	return 10*f[l]>=9*l;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);lst=1;
		int l=strlen(s);
		for(int j=0;j<l;j++)
			insert(s[j]-'0');
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		int l=strlen(s);
		match(l);
		int L=0,R=l;
		while(L<=R)
		{
			int mid=(L+R)/2;
			if(check(mid,l)) L=mid+1;
			else R=mid-1;
		}
		printf("%d\n",R);
	}
	return 0;
}
