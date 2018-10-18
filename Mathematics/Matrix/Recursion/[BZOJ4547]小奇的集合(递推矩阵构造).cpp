#include<bits/stdc++.h>
#define Mod 10000007
using namespace std;
 
struct Matrix
{
    int m,n;
    int a[110][110];
} A,B;
 
Matrix operator * (const Matrix &a,const Matrix &b)
{
    Matrix c;
    c.m=a.m;c.n=b.n;
    for(int i=1;i<=a.m;i++)
        for(int j=1;j<=b.n;j++)
        {
            c.a[i][j]=0;
            for(int k=1;k<=a.n;k++)
                c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j]%Mod)%Mod;
        }
    return c;
}
 
Matrix operator ^ (Matrix a,int b)
{
    Matrix ans=a;b--;
    while(b)
    {
        if(b&1) ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
 
int main()
{
    int n,k,x,ans1=0,a1,a2;
    scanf("%d%d",&n,&k);
    scanf("%d%d",&a1,&a2);
    if(a1<a2) swap(a1,a2);
    for(int i=3;i<=n;i++)
    {
        scanf("%d",&x);
        if(x>a1) ans1=(ans1+a2)%Mod,a2=a1,a1=x;
        else if(x>a2) ans1=(ans1+a2)%Mod,a2=x;
        else ans1=(ans1+x)%Mod;
    }
    ans1=(ans1+a1+a2)%Mod;
    if(a1<=0&&a2<=0)
    {
        ans1=(ans1+1ll*k*(a1+a2)%Mod)%Mod;
        cout<<ans1<<endl;
        return 0;
    }
    while(a2<=0&&k>0) a2=a1+a2,ans1=(ans1+a2)%Mod,k--;
    if(k==0){cout<<ans1<<endl;return 0;}
    B.m=3;B.n=1;
    B.a[2][1]=a1;B.a[3][1]=a2;
    A.m=A.n=3;
    A.a[1][1]=A.a[1][2]=A.a[1][3]=1;
    A.a[2][2]=A.a[2][3]=A.a[3][2]=1;
    B=(A^k)*B;
    cout<<((ans1+B.a[1][1])%Mod+Mod)%Mod<<endl;
    return 0;
}
