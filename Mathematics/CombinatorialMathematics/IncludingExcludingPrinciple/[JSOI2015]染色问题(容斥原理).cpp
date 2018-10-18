#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=400;
int C[N+10][N+10];

void Init()
{
    for(int i=0;i<=N;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%ha;
    }
}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    int n,m,c;Init();
    cin>>n>>m>>c;
    int ans=0;
    for(int k=0;k<=c;k++)
    {
        int now=Pow(c-k+1,n);
        int invn=Pow(c-k+1,ha-2);
        for(int i=0;i<=n;i++)
        {
            int cur=Pow(now,m);
            int invc=Pow(now,ha-2);
            for(int j=0;j<=m;j++)
            {
                int res=1ll*C[n][i]*C[m][j]%ha*C[c][k]%ha;
                res=1ll*res*cur%ha;
                cur=1ll*cur*invc%ha;
                if((i+j+k)&1) ans=(ans-res+ha)%ha;
                else ans=(ans+res)%ha;
            }
            now=1ll*now*invn%ha;
        }
    }
    cout<<ans<<endl;
    return 0;
}