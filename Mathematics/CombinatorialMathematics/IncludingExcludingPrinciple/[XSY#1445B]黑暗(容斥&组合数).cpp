#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=1010;
int C[N][N];
int n,a,b,m;
int X[N],Y[N];
int R[2],G[2],B[2];
int RG[2],RB[2],GB[2];
int RGB[2];

int calc(int d)
{
    if((d&1)!=(m&1)) return 0;
    if(d>m) return 0;
    return C[m][(m+d)/2];
}

void gao(int *A,int al,int ar,int d)
{
    for(int i=al;i<=ar;i++)
    {
        int rc=1,gc=1,bc=1;
        for(int j=1;j<=a;j++) rc=1ll*rc*calc(abs(A[j]-i))%ha;
        for(int j=a+1;j<=a+b;j++) gc=1ll*gc*calc(abs(A[j]-i))%ha;
        for(int j=a+b+1;j<=n;j++) bc=1ll*bc*calc(abs(A[j]-i))%ha;
        R[d]=(R[d]+rc)%ha;
        G[d]=(G[d]+gc)%ha;
        B[d]=(B[d]+bc)%ha;
        RG[d]=(RG[d]+1ll*rc*gc)%ha;
        RB[d]=(RB[d]+1ll*rc*bc)%ha;
        GB[d]=(GB[d]+1ll*gc*bc)%ha;
        RGB[d]=(RGB[d]+1ll*rc*gc%ha*bc)%ha;
    }
}

int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&m);
    for(int i=1,x,y;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        X[i]=x+y;Y[i]=y-x;
    }
    for(int i=0;i<=1000;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    }
    gao(X,-3000,3000,0);
    gao(Y,-3000,3000,1);
    int r=1ll*R[0]*R[1]%ha;
    int g=1ll*G[0]*G[1]%ha;
    int b=1ll*B[0]*B[1]%ha;
    int rg=1ll*RG[0]*RG[1]%ha;
    int rb=1ll*RB[0]*RB[1]%ha;
    int gb=1ll*GB[0]*GB[1]%ha;
    int rgb=1ll*RGB[0]*RGB[1]%ha;
    int ans=1ll*r*g%ha*b%ha;
    ans=(ans-1ll*rg*b%ha+ha)%ha;
    ans=(ans-1ll*rb*g%ha+ha)%ha;
    ans=(ans-1ll*gb*r%ha+ha)%ha;
    ans=(ans+2ll*rgb)%ha;
    printf("%d\n",ans);
    return 0;
}