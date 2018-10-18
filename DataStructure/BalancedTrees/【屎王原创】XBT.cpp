#include<iostream>
#include<cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
struct Node
{
    Node* son[2];
    int depth[2],v,cnt,sum;
}* root;
int tt;
void updata(Node* &o)
{
    if(o==NULL) return;
    o->sum=o->cnt;
    o->depth[0]=o->depth[1]=0;
    if(o->son[0]!=NULL) { o->sum+=o->son[0]->sum; o->depth[0]=max(o->son[0]->depth[0],o->son[0]->depth[1])+1; }
    if(o->son[1]!=NULL) { o->sum+=o->son[1]->sum; o->depth[1]=max(o->son[1]->depth[0],o->son[1]->depth[1])+1; }
}
void rotate(Node* &o,int d)
{
    Node* k=o->son[d^1];
    o->son[d^1]=k->son[d];
    k->son[d]=o;
    updata(o);
    updata(k);
    o=k;
}

void insert(Node* &o,int x)
{
    if(o==NULL)
    {
        o=new Node();
        o->son[0]=o->son[1]=NULL;
        o->depth[0]=0; o->depth[1]=0;
        o->v=x;
        o->sum=o->cnt=1;
    }
    else if(o->v==x){o->cnt++;updata(o);return;}
    else
    {
        if(o->v>x) insert(o->son[0],x); else insert(o->son[1],x);
        if (o->depth[0]>o->depth[1]+1) rotate(o,1);
            else if (o->depth[1]>o->depth[0]+1) rotate(o,0);
                else updata(o);
    }
    
}
void remove(Node* &o,int x)
{
    if(o==NULL) return;
    if(o->v>x) remove(o->son[0],x);
    if(o->v<x) remove(o->son[1],x);
    if(o->v==x)
    {
        if(o->cnt>0) o->cnt--;
        if(o->cnt==0)
        {
            if(o->son[0]==NULL) o=o->son[1];
            else if(o->son[1]==NULL) o=o->son[0];
            else
            {
                if(o->depth[0]>o->depth[1]){rotate(o,1);remove(o->son[1],x);}
                else{rotate(o,0);remove(o->son[0],x);}
            }
        }
    }
    if(o!=NULL) updata(o);
}
int rank(Node* &o,int x)
{
    if(o==NULL) return 0;
    int ans=0;
    if(o->son[0]!=NULL) ans=o->son[0]->sum;
    if(o->v==x) return ans+1;
    if(o->v>x) return rank(o->son[0],x);
    if(o->v<x) return ans+o->cnt+rank(o->son[1],x);
}
int kth(Node* &o,int x)
{
    if(o==NULL) return 0;
    int now=0;
    if(o->son[0]!=NULL) now=o->son[0]->sum;
    if(now<x&&x<=now+o->cnt) return o->v;
    if(x<=now) return kth(o->son[0],x);
    if(now+o->cnt<x) return kth(o->son[1],x-now-o->cnt);
}
void pre(Node* &o,int x,int &ans)
{
    if(o==NULL) return;
    if(o->v<x)
    {
        ans=max(ans,o->v);
        pre(o->son[1],x,ans);
    }
    else pre(o->son[0],x,ans);
}
void suc(Node* &o,int x,int &ans)
{
    if(o==NULL) return;
    if(o->v>x)
    {
        ans=min(ans,o->v);
        suc(o->son[0],x,ans);
    }
    else suc(o->son[1],x,ans);
}
int main()
{
    int n,opt,num;
    //freopen("data.in","r",stdin);
    //freopen("data.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&opt,&num);
        if(opt==1) insert(root,num);
        if(opt==2) remove(root,num);
        if(opt==3) printf("%d\n",rank(root,num));
        if(opt==4) printf("%d\n",kth(root,num));
        if(opt==5){int ans=-0x7fffffff;pre(root,num,ans);printf("%d\n",ans);}
        if(opt==6){int ans=0x7fffffff;suc(root,num,ans);printf("%d\n",ans);}
        if (opt==7) printf("%d %d\n",root->depth[0],root->depth[1]);
    }
    return 0;
}
