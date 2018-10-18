#include<bits/stdc++.h>
using namespace std;

int heap[1000010],sz=0;

void push(int x)
{
	heap[++sz]=x;
	int p=sz,fa=sz/2;
	while(fa>0)
	{
		if(heap[p]<heap[fa]) swap(heap[p],heap[fa]);
		p=fa;fa=p/2;
	}
}

void del()
{
	heap[1]=heap[sz--];
	int fa=1,p=fa*2;
	while(p<=sz)
	{
		if(p+1<=sz&&heap[p+1]<heap[p]) p++;
		if(heap[p]<heap[fa]) swap(heap[p],heap[fa]);
		else break;
		fa=p;p=fa*2;
	}
}

int main()
{
	int n,opt,x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&opt);
		if(opt==1){scanf("%d",&x);push(x);}
		if(opt==2) printf("%d\n",heap[1]);
		if(opt==3) del();
	}
	return 0;
}
