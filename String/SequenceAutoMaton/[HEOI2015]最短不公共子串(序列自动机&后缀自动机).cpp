#include<bits/stdc++.h>
using namespace std;

struct SAM
{
	int ch[4010][26],prt[4010];
	int len[4010];
	int lst,tot;
	SAM(){lst=tot=1;}
	
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
} SA,SB;

struct SqAM
{
	int ch[4010][26],lst[26],pre[4010];
	int root,tot;
	SqAM(){root=tot=1;for(int i=0;i<26;i++)lst[i]=1;}
	
	void insert(int c)
	{
		int p=lst[c],np=++tot;
		pre[np]=p;
		for(int i=0;i<26;i++)
			for(int j=lst[i];j&&!ch[j][c];j=pre[j])
				ch[j][c]=np;
		lst[c]=np;
	}
} SQA,SQB;

char A[2010],B[2010];
int la,lb;
struct THIRD
{
	int a,b,step;
	THIRD(int x=0,int y=0,int z=0):a(x),b(y),step(z){}
};
int vis[4010][4010];

int BFS1()
{
	queue<THIRD> q;
	q.push(THIRD(1,1,0));
	vis[1][1]=1;
	while(!q.empty())
	{
		int ra=q.front().a,rb=q.front().b,st=q.front().step;
		for(int i=0;i<26;i++)
		{
			int va=SA.ch[ra][i],vb=SB.ch[rb][i];
			if(va&&vb)
			{
				if(vis[va][vb]==1) continue;
				q.push(THIRD(va,vb,st+1));
				vis[va][vb]=1;
			}
			if(va&&!vb) return st+1;
		}
		q.pop();
	}
	return -1;
}

int BFS2()
{
	queue<THIRD> q;
	q.push(THIRD(1,1,0));
	vis[1][1]=2;
	while(!q.empty())
	{
		int ra=q.front().a,rb=q.front().b,st=q.front().step;
		for(int i=0;i<26;i++)
		{
			int va=SA.ch[ra][i],vb=SQB.ch[rb][i];
			if(va&&vb)
			{
				if(vis[va][vb]==2) continue;
				q.push(THIRD(va,vb,st+1));
				vis[va][vb]=2;
			}
			if(va&&!vb) return st+1;
		}
		q.pop();
	}
	return -1;
}

int BFS3()
{
	queue<THIRD> q;
	q.push(THIRD(1,1,0));
	vis[1][1]=3;
	while(!q.empty())
	{
		int ra=q.front().a,rb=q.front().b,st=q.front().step;
		for(int i=0;i<26;i++)
		{
			int va=SQA.ch[ra][i],vb=SB.ch[rb][i];
			if(va&&vb)
			{
				if(vis[va][vb]==3) continue;
				q.push(THIRD(va,vb,st+1));
				vis[va][vb]=3;
			}
			if(va&&!vb) return st+1;
		}
		q.pop();
	}
	return -1;
}

int BFS4()
{
	queue<THIRD> q;
	q.push(THIRD(1,1,0));
	vis[1][1]=4;
	while(!q.empty())
	{
		int ra=q.front().a,rb=q.front().b,st=q.front().step;
		for(int i=0;i<26;i++)
		{
			int va=SQA.ch[ra][i],vb=SQB.ch[rb][i];
			if(va&&vb)
			{
				if(vis[va][vb]==4) continue;
				q.push(THIRD(va,vb,st+1));
				vis[va][vb]=4;
			}
			if(va&&!vb) return st+1;
		}
		q.pop();
	}
	return -1;
}

int main()
{
	scanf("%s%s",A,B);
	la=strlen(A),lb=strlen(B);
	for(int i=0;i<la;i++) SA.insert(A[i]-'a'),SQA.insert(A[i]-'a');
	for(int i=0;i<lb;i++) SB.insert(B[i]-'a'),SQB.insert(B[i]-'a');
	printf("%d\n%d\n%d\n%d\n",BFS1(),BFS2(),BFS3(),BFS4());
	return 0;
}
