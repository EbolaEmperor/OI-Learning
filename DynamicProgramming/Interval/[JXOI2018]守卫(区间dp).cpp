#include<bits/stdc++.h>
using namespace std;

const int N=5010;
int f[N][N],h[N],n;

double slope(int l,int r){return (double)(h[r]-h[l])/(r-l);}
bool cansee(int l,int x,int r){return slope(x,r)>slope(l,r);}

int main()
{
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    for(int r=1;r<=n;r++)
    {
        ans^=(f[r][r]=1);
        int sum=1,p=0;
        for(int l=r-1;l>=1;l--)
        {
            if(!p||cansee(l,p,r)) sum+=min(f[l+1][p-1],f[l+1][p]),p=l;
            ans^=(f[l][r]=sum+min(f[l][p-1],f[l][p]));
        }
    }
    cout<<ans<<endl;
    return 0;
}