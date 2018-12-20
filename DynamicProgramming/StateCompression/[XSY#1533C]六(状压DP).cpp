#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=1e9+7;
struct node
{
    int x,y;
    node(int _x=0,int _y=0):x(_x),y(_y){}
    bool operator < (const node &a) const{return y==a.y?x<a.x:y<a.y;}
};
int p[9],cnt[9],cp=0;
int g[100],f[300000];
set<node> s;
int ans=0,a[9];
LL n;

node calc(int x)
{
    int used=0,tot=0;
    static int b[9],p[9];
    memset(b,0,sizeof(b));
    memset(p,0,sizeof(p));
    for(int i=1;i<=cp;i++)
    {
        b[i]=a[i];
        if(x&(1<<i-1))
        {
            if(!b[i]){b[i]=6;continue;}
            if(!used&&b[i]) used=b[i];
            if(b[i]==7) return node(-1,0);
            if(used&&b[i]&&used!=b[i]) return node(-1,0);
            b[i]=7;
        }
    }
    int stu=0,len=0;p[7]=7;
    for(int i=1;i<=cp;i++) if(b[i]&&!p[b[i]]) p[b[i]]=++tot;
    for(int i=1;i<=cp;i++) b[i]=p[b[i]];
    for(int i=cp;i>=1;i--) stu=stu<<3|b[i];
    for(int i=1;i<=cp;i++) if(b[i]) len+=1+(b[i]==7);
    return node(stu,len);
}

void gao()
{
    s.insert(node(0,0));
    while(!s.empty())
    {
        int x=s.begin()->x,v=x;s.erase(s.begin());
        for(int i=1;i<=cp;i++) a[i]=v&7,v>>=3;
        ans=(ans+f[x])%ha;
        for(int t=1;t<(1<<cp);t++)
        {
            node nxt=calc(t);
            if(nxt.x==-1) continue;
            if(!f[nxt.x]) s.insert(nxt);
            f[nxt.x]=(f[nxt.x]+1ll*f[x]*g[t])%ha;
        }
    }
}

int main()
{
    cin>>n;
    for(LL i=2;i*i<=n;i++)
    {
        if(n%i) continue;
        p[++cp]=i;
        while(n%i==0) cnt[cp]++,n/=i;
    }
    if(n>1) p[++cp]=n,cnt[cp]=1;
    for(int s=1;s<(1<<cp);s++)
    {
        g[s]=1;
        for(int i=1;i<=cp;i++)
            if(s&(1<<i-1)) g[s]=1ll*g[s]*cnt[i]%ha;
    }
    f[0]=1;gao();
    printf("%d\n",ans-1);
    return 0;
}