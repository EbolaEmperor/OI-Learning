#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x;
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using namespace IO;
const int N=1000010;
vector<int> loop[N];
int n,tot=0,nxt[N],stu[N],ans[N];
bool vis[N];

void gao(int u)
{
    tot++;
    for(;!vis[u];u=nxt[u])
        loop[tot].emplace_back(u),vis[u]=1;
    int n=loop[tot].size();
    if(n&1)
    {
        vector<int> lp;lp.resize(n);
        for(int i=0;i<n;i++)
            lp[i*2%n]=loop[tot][i];
        for(int i=0;i<n-1;i++)
            ans[lp[i]]=lp[i+1];
        ans[lp.back()]=lp[0];
    }
    else if(!stu[n]) stu[n]=tot;
    else
    {
        int pre=stu[n];stu[n]=0;
        loop[tot].emplace_back(loop[tot][0]);
        for(int i=0;i<n;i++)
        {
            ans[loop[tot][i]]=loop[pre][i];
            ans[loop[pre][i]]=loop[tot][i+1];
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) nxt[read()]=i;
    for(int i=1;i<=n;i++) if(!vis[i]) gao(i);
    for(int i=1;i<=n;i++) if(stu[i]) return puts("-1"),0;
    for(int i=1;i<=n;i++) print(ans[i]),putc(' ');
    return putc('\n'),flush(),0;
}