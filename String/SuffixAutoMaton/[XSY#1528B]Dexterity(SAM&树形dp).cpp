#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=400010;
int len[N],prt[N],rgt[N];
int ch[N][3],lst=1,tot=1;
int s[N],n,w[N],d[N];
LL sumw[N];
char ss[N];

void insert(int c)
{
    int p=lst,np=++tot;rgt[np]=len[np]=len[p]+1;
    while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
    if(!p) prt[np]=1;
    else
    {
        int q=ch[p][c];
        if(len[p]+1==len[q]) prt[np]=q;
        else
        {
            int nq=++tot;len[nq]=len[p]+1;rgt[nq]=rgt[np];
            memcpy(ch[nq],ch[q],sizeof(ch[nq]));
            prt[nq]=prt[q];prt[q]=prt[np]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
        }
    }
    lst=np;
}

LL dp(int u)
{
    if(!u) return 1ll<<60;
    int now=len[prt[u]];LL f[3],res=0;
    if(len[u]>=n) return sumw[n]-sumw[now+1];
    for(int k=0;k<3;k++) f[k]=dp(ch[u][k]);
    for(int k=0;k<3;k++)
    {
        LL resp=1ll<<60;
        for(int i=0;i<3;i++)
        {
            int tmp=0;
            if(k==i) tmp=d[len[u]+1];
            if((k+1)%3==i) tmp=w[len[u]+1];
            resp=min(resp,f[i]+tmp);
        }
        res=max(res,resp);
    }
    if(len[u]>now) res+=sumw[len[u]]-sumw[now+1];
    return res;
}

LL gao()
{
    for(int i=1;i<=n;i++)
        sumw[i]=sumw[i-1]+w[i];
    memset(ch,0,sizeof(ch));
    for(int i=1;i<=tot;i++)
        ch[prt[i]][s[rgt[i]-len[prt[i]]]]=i;
    return dp(1);
}

int main()
{
    scanf("%d%s",&n,ss+1);
    for(int i=1;i<=n;i++)
        scanf("%d%d",w+i,d+i);
    for(int i=1;i<=n;i++)
    {
        if(ss[i]=='r') s[i]=0;
        if(ss[i]=='s') s[i]=1;
        if(ss[i]=='p') s[i]=2;
        s[i+n]=s[i];
    }
    reverse(s+1,s+2*n+1);
    for(int i=1;i<=2*n;i++)
        insert(s[i]);
    printf("%lld\n",gao());
    return 0;
}