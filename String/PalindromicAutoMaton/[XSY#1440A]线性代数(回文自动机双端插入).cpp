#include<bits/stdc++.h>
using namespace std;
 
const int N=400010;
int s[N],m;
int ch[N][4],sz;
int fail[N],dep[N];
int lst[2],pos[2];
int len[N];
long long ans=0;
 
int newnode(int l){len[++sz]=l;return sz;}
 
void init()
{
    sz=-1;
    pos[0]=m+5;pos[1]=m+4;
    lst[0]=lst[1]=0;
    newnode(0);
    newnode(-1);
    fail[0]=1;
    memset(s,-1,sizeof(s));
}
 
int find(int p,int d)
{
    while(s[pos[d]]!=s[pos[d]+(d?-len[p]-1:len[p]+1)]) p=fail[p];
    return p;
}
 
void insert(int c,int d)
{
    if(d) s[++pos[1]]=c;
    else s[--pos[0]]=c;
    int cur=find(lst[d],d);
    if(!ch[cur][c])
    {
        int now=newnode(len[cur]+2);
        fail[now]=ch[find(fail[cur],d)][c];
        dep[now]=dep[fail[now]]+1;
        if(len[now]==pos[1]-pos[0]+1) lst[d^1]=now;
        ch[cur][c]=now;
    }
    lst[d]=ch[cur][c];
    ans+=dep[lst[d]];
}
 
int main()
{
    scanf("%d",&m);init();
    char opt[10],c[10];
    while(m--)
    {
        scanf("%s%s",opt,c);
        insert(c[0]-'a',opt[0]=='r');
        printf("%lld %d\n",ans,sz-1);
    }
    return 0;
}