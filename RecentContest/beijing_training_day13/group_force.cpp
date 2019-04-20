#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=50010;
char s[N];
int n,q;

struct DMK
{
    int A,B,C,D,id;
    void init(){scanf("%d%d%d%d",&A,&B,&C,&D);id=1;}
    void get(int &l,int &r)
    {
        l=min(A,B);
        r=max(A,B);
        A=((A^id)+C)%n+1;
        B=((B^id)+D)%n+1;
        id++;
    }
} dmk;

int query()
{
    int l,r;
    dmk.get(l,r);
    static int f[N],g[N],h[N];
    f[l-1]=1;
    g[l-1]=l-1;
    h[l-1]=1ll*(l-1)*(l-1)%ha;
    for(int i=l;i<r;i++)
    {
        f[i]=f[i-1];
        g[i]=g[i-1];
        h[i]=h[i-1];
        if(s[i]=='1') continue;
        int cur=(1ll*i*i%ha*f[i-1]-2ll*i*g[i-1]+h[i-1])%ha;
        f[i]=(f[i]+cur)%ha;
        g[i]=(g[i]+1ll*i*cur)%ha;
        h[i]=(h[i]+1ll*i*i%ha*cur)%ha;
    }
    int cur=(1ll*r*r%ha*f[r-1]-2ll*r*g[r-1]+h[r-1])%ha;
    return (cur+ha)%ha;
}

int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    dmk.init();
    int ans=0;
    while(q--) ans^=query();
    printf("%d\n",ans);
    return 0;
}
