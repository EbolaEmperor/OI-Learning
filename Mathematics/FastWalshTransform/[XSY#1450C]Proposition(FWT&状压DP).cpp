#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=400010;
int f[75][N],rf[75][N];
int len,n,K,m,p,Q;
bool val[7];
char s[4010];

inline int add(const int &x,const int &y){return x+y>=ha?x+y-ha:x+y;}
inline int dev(const int &x,const int &y){return x-y<0?x-y+ha:x-y;}
inline int rev(const int &x){return x^(len-1);}

void FWT(int *a,int d)
{
    for(int i=1;i<len;i<<=1)
        for(int j=0;j<len;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=a[i+j+k];
                if(d==1) a[i+j+k]=add(x,y);
                else a[i+j+k]=dev(y,x);
            }
}

void prework()
{
    len=1<<(1<<K);
    for(int i=0;i<K;i++)
    {
        int stu=0;
        for(int s=0;s<1<<K;s++)
            if(s&(1<<i)) stu|=1<<s;
        f[0][stu]++;
        rf[0][rev(stu)]++;
    }
    FWT(f[0],1);FWT(rf[0],1);
    for(int i=1;i<=n;i++)
    {
        memcpy(f[i],rf[i-1],sizeof(f[i]));
        for(int j=0;j<i;j++)
            for(int k=0;k<len;k++)
                f[i][k]=(f[i][k]+1ll*rf[j][k]*f[i-1-j][k])%ha;
        FWT(f[i],-1);
        for(int k=0;k<len;k++)
            rf[i][k]=f[i][rev(k)];
        if(i<n) FWT(f[i],1),FWT(rf[i],1);
    }
}

bool calc()
{
    if(s[p]=='Q') return p++,Q;
    if(s[p]=='x')
    {
        bool res=val[s[p+1]-'1'];
        return p++,p++,res;
    }
    if(s[++p]=='~')
    {
        p++;bool res=calc();
        return p++,!res;
    }
    bool a=calc();
    p++;p++;
    bool b=calc();
    return p++,!a||b;
}

int query()
{
    static bool g[2][N];
    for(Q=0;Q<2;Q++)
        for(int s=0;s<1<<K;s++)
        {
            for(int k=0;k<K;k++)
                val[k]=(s>>k)&1;
            p=1;g[Q][s]=calc();
        }
    int ans=0;
    for(int t=0;t<len;t++)
    {
        if(!f[n][t]) continue;
        for(int s=0;s<1<<K;s++)
            if(!g[(t>>s)&1][s]) goto fuck;
        ans=add(ans,f[n][t]);
        fuck : ;
    }
    return ans;
}

int main()
{
    scanf("%d%d",&n,&K);
    prework();
    scanf("%d",&m);
    while(m--)
    {
        scanf("%s",s+1);
        printf("%d\n",query());
    }
    return 0;
}