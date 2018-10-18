#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Node
{
    Node* son[2];
    int v;
    int r;
    int cnt;
    int sum;
};
int down,sum=0;
Node* root;

void maintain(Node* &o)
{
    o->sum=o->cnt;
    if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
    if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
}

void rotate(Node* &o,int d)
{
    Node* k=o->son[d^1];
    o->son[d^1]=k->son[d];
    k->son[d]=o;
    maintain(o);
    maintain(k);
    o=k;
}

void insert(Node* &o,int x)
{
    if(o==NULL)
    {
        o=new Node;
        o->son[0]=o->son[1]=NULL;
        o->cnt=o->sum=1;
        o->r=rand();
        o->v=x;
    }
    else
    {
        if(x==o->v) o->cnt++,maintain(o);
        else if(x<o->v)
        {
            insert(o->son[0],x);
            if(o->son[0]->r>o->r) rotate(o,1);else maintain(o);
        }
        else if(x>o->v)
        {
            insert(o->son[1],x);
            if(o->son[1]->r>o->r) rotate(o,0);else maintain(o);
        }
    }
}

int kth(Node* &o,int k)
{
    if(k<1||k>o->sum) return -1;
    int ss=0;
    if(o->son[0]!=NULL) ss=o->son[0]->sum;
    if(k>ss&&k<=ss+o->cnt) return o->v;
    if(k<=ss) return kth(o->son[0],k);
    if(k>ss+o->cnt) return kth(o->son[1],k-ss-o->cnt);
}

void remove(Node* &o)     //改进版删除
{
    if(o==NULL) return;
	if(o->v>=down) remove(o->son[0]);
	else
	{
		if(o->son[0]!=NULL) sum+=o->son[0]->sum;
		sum+=o->cnt;
		o=o->son[1];
		remove(o);
	}
	if(o!=NULL) maintain(o);
}

void add(Node* &o,int k)     //暴力加减
{
    if(o->son[0]!=NULL) add(o->son[0],k);
    o->v+=k;
    if(o->son[1]!=NULL) add(o->son[1],k);
}

int main()
{
    int n,x;
    char opt;
    cin>>n>>down;
    for(int T=1;T<=n;T++)
    {
        scanf(" %c%d",&opt,&x);
        if(opt=='I'&&x>=down) insert(root,x);
        if(opt=='A') add(root,x);
        if(opt=='S') add(root,-x),remove(root);
        if(opt=='F')
        {
            if(root!=NULL) printf("%d\n",kth(root,root->sum-x+1));
            else printf("-1\n");
        }
    }
    cout<<sum<<endl;
    return 0;
}
