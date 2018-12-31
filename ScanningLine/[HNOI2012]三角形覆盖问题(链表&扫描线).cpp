#include<bits/stdc++.h>
using namespace std;

struct TRI{int x,y,d,r;} tr[10010];
struct Node
{
	Node *pre,*nxt;int p;
	Node(){p=0;pre=nxt=NULL;}
};
Node *head,*tail;
int mark[2000010];

bool operator < (const TRI &a,const TRI &b){return a.x<b.x;}

void del(Node* &p)
{
	if(p->pre==NULL&&p->nxt==NULL){head=tail=NULL;return;}
	if(p->nxt==NULL){p->pre->nxt=p->nxt;tail=p->pre;return;}
	if(p->pre==NULL){p->nxt->pre=p->pre;head=p->nxt;return;}
	p->pre->nxt=p->nxt;p->nxt->pre=p->pre;
}

void push_back(int x)
{
	Node *q=tail;tail=new Node;
	tail->p=x;tail->pre=q;
	if(q!=NULL) q->nxt=tail;
	if(head==NULL) head=tail;
}

int main()
{
	int n,tot=0,k=1,x,y,d,tt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		tot++;scanf("%d%d%d",&tr[tot].x,&tr[tot].y,&tr[tot].d);
		tr[tot].r=tr[tot].y+tr[tot].d;
		if(tr[tot].d==0){tot--;continue;}
		tt=max(tt,tr[tot].x+tr[tot].d);
	}
	sort(tr+1,tr+1+tot);
	int len=0,lst=0,ans=0;
	for(int i=0;i<=tt;i++)
	{
		len=lst;
		for(Node *p=head;p!=NULL;p=p->nxt)
		{
			mark[tr[p->p].r]--;
			if(!mark[tr[p->p].r]) len--;
			tr[p->p].r--;
			if(tr[p->p].r==tr[p->p].y) del(p);
		}
		ans+=len+lst;
		lst=len;
		while(k<=tot)
		{
			if(tr[k].x==i)
			{
				push_back(k);
				for(int j=tr[k].y+1;j<=tr[k].r;j++)
				{
					if(!mark[j]) lst++;
					mark[j]++;
				}
			}
			else break;
			k++;
		}
	}
	printf("%.1lf\n",(double)ans/2.0);
	return 0;
}
