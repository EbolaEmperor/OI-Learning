#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=600010;
int n,m,a[N],b[N],c[N],bit[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

void FWT(int *a,int n)
{
    for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=a[i+j+k];
                a[j+k]=add(x,y);
                a[i+j+k]=mns(x,y);
            }
}

int main()
{
    scanf("%d",&n);
    int mx=0,xsum=0,ans;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        mx=max(mx,a[i]);
        b[a[i]]=1;
        xsum^=a[i];
    }
    for(m=1;m<=mx;m<<=1);FWT(b,m);
    for(int i=1;i<m;i++) bit[i]=bit[i^(i&-i)]+1;
    for(int i=0;i<m;i++) c[i]=(bit[i&xsum]&1)?ha-1:1;
    for(ans=n;;ans--)
    {
        int res=0;
        for(int i=0;i<m;i++) res=add(res,c[i]);
        if(res) break;
        for(int i=0;i<m;i++)
            c[i]=1ll*c[i]*b[i]%ha;
    }
    printf("%d\n",ans);
    return 0;
}