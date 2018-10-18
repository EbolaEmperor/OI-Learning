#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
typedef long double LD;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline ULL read()
{
    ULL x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

ULL base[70],b[70];
int n,m,K;
__int128 ans=0;
ULL tot=1;
ULL C[65][65];

void insert(ULL x)
{
    for(int i=63;i>=0;i--)
        if(x&(1ull<<i))
        {
            if(base[i]) x^=base[i];
            else{base[i]=x;break;}
        }
}

__int128 P(ULL x){__int128 res=1;for(int i=1;i<=K;i++) res*=x;return res;}

void dfs(int p,ULL cur)
{
    if(p==m){ans+=P(cur);return;}
    dfs(p+1,cur^b[p]);
    dfs(p+1,cur);
}

void Task1()
{
    for(int i=1;i<=m;i++) tot*=2ull;
    dfs(0,0);
    if(ans==0){puts("0");return;}
    __int128 tmp=ans/(tot/2);
    ULL ttt=tmp/2;cout<<ttt;
    if(tmp&1) puts(".5");
}

void Task2()
{
    for(int i=0;i<=63;i++)
    {
        C[i][0]=1ull;
        for(int j=1;j<=i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    LD pw2=1,ans=0;
    for(int k=0;k<=63;k++,pw2*=2)
    {
        LD res=0;int c=0;
        for(int i=0;i<=63;i++) c+=bool(base[i]&(1ull<<k));
        for(int i=1;i<=(c+1)/2;i++) res+=C[c][2*i-1];
        LD tmp=1;for(int i=1;i<=c;i++) tmp*=2;
        ans+=res*pw2/tmp;
    }
    if(abs(ans-round(ans))<0.1) printf("%.0Lf",ans);
    else printf("%.1Lf\n",ans);
}

__int128 dp(int x,int y)
{
    int S[65]={0};
    __int128 f[2][4]={0};
    for(int i=0;i<m;i++)
        S[i]=(((b[i]>>x)&1)<<1)+((b[i]>>y)&1);
    f[0][0]=1;int k=1;
    for(int i=0;i<m;i++,k^=1)
        for(int s=0;s<=3;s++)
            f[k][s]=f[k^1][s]+f[k^1][s^S[i]];
    return f[k^1][3];
}

void Task3()
{
    __int128 ans1=0,ans2=0,pwm=1;
    for(int i=1;i<=m;i++) pwm*=2;
    for(int j=0;j<=63;j++)
        for(int k=0;k<=63;k++)
        {
            __int128 pw2=1,res=dp(j,k);
            for(int i=1;i<=j+k;i++) pw2*=2;
            if(j+k>=m) ans1+=res*(pw2/pwm);
            else ans2+=res*pw2;
        }
    __int128 tmp=ans2/(pwm/2)+ans1*2;
    ULL ttt=tmp/2;cout<<ttt;
    if(tmp&1) puts(".5");
}

int main()
{
    n=read();K=read();
    for(int i=1;i<=n;i++) insert(read());
    for(int i=0;i<=63;i++) if(base[i]) b[m++]=base[i];
    if(K>=3) Task1();
    if(K==1) Task2();
    if(K==2) Task3();
    return 0;
}