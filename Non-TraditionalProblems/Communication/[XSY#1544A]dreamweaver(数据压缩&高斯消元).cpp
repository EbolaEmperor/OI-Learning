#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=65537;

static int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

vector<int> encode(vector<int>arr,int lim)
{
    static int b[16];
    for(int i=0;i<8;i++)
    {
        LL t=arr[i]+(LL)INT_MAX;
        b[i<<1]=t%ha;
        b[i<<1|1]=t/ha;
    }
    vector<int> res;
    for(int x=0;x<1000;x++)
    {
        int y=0;
        for(int j=0,tx=1;j<16;j++)
        {
            y=(y+(LL)tx*b[j])%ha;
            tx=(LL)tx*x%ha;
        }
        res.push_back(y<<10|x);
    }
    return res;
}

vector<int> decode(int(*const arr)(int),int n,int lim)
{
    static int g[16][17];
    static LL ans[16];
    for(int i=0;i<16;i++)
    {
        int a=arr(i),x=a&1023,y=a>>10;
        for(int j=0,tx=1;j<16;j++)
            g[i][j]=tx,tx=(LL)tx*x%ha;
        g[i][16]=y;
    }
    for(int i=0;i<16;i++)
    {
        int p=i;
        while(!g[p][i]) p++;
        for(int j=0;j<17;j++) swap(g[i][j],g[p][j]);
        int inv=Pow(g[i][i],ha-2);
        for(int j=i+1;j<16;j++)
        {
            int t=1ll*g[j][i]*inv%ha;
            for(int k=0;k<17;k++)
                g[j][k]=(g[j][k]-(LL)t*g[i][k]%ha+ha)%ha;
        }
    }
    for(int i=15;i>=0;i--)
    {
        LL c=g[i][16];
        for(int j=i+1;j<16;j++)
            c=(c-ans[j]*g[i][j]%ha+ha)%ha;
        ans[i]=c*Pow(g[i][i],ha-2)%ha;
    }
    vector<int> res;
    for(int i=0;i<8;i++)
        res.push_back(ans[i<<1]+ans[i<<1|1]*ha-INT_MAX);
    return res;
}