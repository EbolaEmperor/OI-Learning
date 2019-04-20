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
    static int f[N][2][2];
    memset(f,0,sizeof(f));
    f[l][0][0]=f[l][0][1]=f[l][1][0]=f[l][1][1]=1;
    for(int i=l+1;i<=r;i++)
    {
        f[i][0][0]=f[i-1][0][0];
        f[i][0][1]=(f[i-1][0][1]+f[i-1][0][0])%ha;
        f[i][1][0]=(f[i-1][1][0]+f[i-1][0][0])%ha;
        f[i][1][1]=(f[i-1][0][0]+f[i-1][1][1]+f[i-1][0][1]+f[i-1][1][0])%ha;
        if(s[i-1]=='0')
        {
            f[i][0][0]=(f[i][0][0]+f[i-1][1][1])%ha;
            f[i][0][1]=(f[i][0][1]+f[i-1][1][1])%ha;
            f[i][1][0]=(f[i][1][0]+f[i-1][1][1])%ha;
            f[i][1][1]=(f[i][1][1]+f[i-1][1][1])%ha;
        }
    }
    return f[r][1][1];
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
