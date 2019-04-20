#include<bits/stdc++.h>
using namespace std;

const int N=1010,M=N*5,ha=1e9+7;
int n,m,q,val[M];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

struct BigBit
{
    int v[N],id;
    bool operator < (const BigBit &a) const
    {
        for(int i=1;i<=n;i++)
            if(v[i]!=a.v[i]) return v[i]<a.v[i];
    }
    int getval()
    {
        int res=0;
        for(int i=1;i<=n;i++)
            res=(res<<1|v[i])%ha;
        return res;
    }
} num[M];

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
    {
        static char s[M];
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            num[j].v[n-i+1]=s[j]-'0';
    }
    for(int i=1;i<=m;i++) num[i].id=i;
    sort(num+1,num+1+m);
    for(int i=1;i<=m;i++)
        val[i]=num[i].getval();
    val[m+1]=Pow(2,n);
    while(q--)
    {
        static char s[M];
        scanf("%s",s+1);
        int L=0,R=m+1;
        for(int i=1;i<=m;i++)
            if(s[num[i].id]-'0'==1)
                {R=i;break;}
        for(int i=m;i>=1;i--)
            if(s[num[i].id]-'0'==0)
                {L=i;break;}
        if(L>=R){puts("0");continue;}
        printf("%d\n",(val[R]-val[L]+ha)%ha);
    }
    return 0;
}
