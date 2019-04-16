#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int ch[N][26],prt[N],len[N],sz[N];
int tot=1,lst=1;
char s[N];
int n,m;

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
            prt[nq]=prt[q];prt[np]=prt[q]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
        }
    }
    lst=np;
    sz[lst]=1;
}

int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        for(int i=l;i<=r;i++)
            insert(s[i]-'a');
        for(int i=tot;i>1;i--)
            sz[prt[i]]+=sz[i];
        int ans=0;
        for(int i=1;i<=tot;i++)
            if(sz[i]>1) ans=max(ans,len[i]);
        printf("%d\n",ans);
        for(int i=1;i<=tot;i++)
        {
            len[i]=sz[i]=prt[i]=0;
            memset(ch[i],0,sizeof(ch[i]));
        }
        tot=lst=1;
    }
    return 0;
}
