#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
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

const int ha=1e9+7;
const int N=1010;
bitset<N> a[N],b[N];
//a：线性基，b[i]：i号线性基与原矩阵哪几行有关
vector<bitset<N>> c; 
//c[i]：第i个执行insert时最后被消成0的向量，与原矩阵的哪几行有关
int p,q,s,m,ol,r=0;
int p2[N*N],ans[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void prework()
{
    p2[0]=1;
    for(int i=1;i<N*N;i++)
        p2[i]=(p2[i-1]<<1)%ha;
    static int f[N][N];
    //p*i的，秩为j的矩阵数量
    static int g[N][N];
    //i*s的，秩为j的矩阵数量
    f[0][0]=1;
    for(int i=0;i<=1000;i++)
        for(int j=0;j<=i;j++)
        {
            if(!f[i][j]) continue;
            f[i+1][j]=(f[i+1][j]+1ll*f[i][j]*p2[j])%ha;
            //不增加秩，前j位任意，j位之后均为0。方案数为：2^j
            f[i+1][j+1]=(f[i+1][j+1]+1ll*f[i][j]*(p2[p]-p2[j]))%ha;
            //增加秩，前j位任意，j位之后至少要有一个1。运用补集转化的思想，方案数为：2^p-2^j
        }
    g[0][0]=1;
    for(int i=0;i<=1000;i++)
        for(int j=0;j<=i;j++)
        {
            if(!g[i][j]) continue;
            g[i+1][j]=(g[i+1][j]+1ll*g[i][j]*p2[j])%ha;
            g[i+1][j+1]=(g[i+1][j+1]+1ll*g[i][j]*(p2[s]-p2[j]))%ha;
        }
    for(int r=0;r<=1000;r++)
    {
        int res=0;
        for(int x=0;x<=q;x++)
            res=(res+1ll*f[q][x]*g[x][r]%ha*p2[s*(q-x)])%ha;
            //矩阵A有x个秩，矩阵B前x行有r个秩，x行后任意
        ans[r]=1ll*res*Pow(f[s][r],ha-2)%ha;
        //res是所有秩为r矩阵C答案之和，除掉秩为r矩阵C个数，得到1个秩为r矩阵C的答案
        if(ans[r]<0) ans[r]+=ha;
    }
}

void insert(bitset<N> s,int x)
{
    bitset<N> t;t[x]=1;
    for(int i=999;i>=0;i--)if(s[i])
    {
        if(!a[i].any())
        {
            a[i]=s;b[i]=t;r++;
            return;
        }
        s^=a[i];
        t^=b[i];
    }
    c.emplace_back(t);
}

void erase(int x)
{
    for(auto &s : c)if(s[x])
    {
        //最后被消成0的所有向量中，若存在与第x行相关的向量，则让它顶上来
        swap(s,c.back());
        for(int i=0;i<1000;i++)
            if(b[i][x]) b[i]^=c.back();
        for(auto &t : c) if(t[x]) t^=c.back();
        c.pop_back();
        return;
    }
    for(int i=0;i<1000;i++)if(b[i][x])
    {
        //没有能顶上来的向量，则将第x行对线性基的影响消除
        for(int j=i+1;j<1000;j++)
            if(b[j][x]) a[j]^=a[i],b[j]^=b[i];
        a[i].reset();b[i].reset();r--;
        return;
    }
}

int main()
{
    p=read();q=read();s=read();
    m=read();ol=read();
    prework();
    for(int i=0;i<p;i++)
    {
        bitset<N> t;
        for(int j=0;j<s;j++)
            t[j]=read();
        insert(t,i);
    }
    int x,lastans=ans[r];
    printf("%d\n",lastans);
    while(m--)
    {
        bitset<N> t;
        x=read()^(ol*lastans);x--;
        for(int i=0;i<s;i++)
            t[i]=read();
        erase(x);insert(t,x);
        printf("%d\n",lastans=ans[r]);
    }
    return 0;
}