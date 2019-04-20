#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int inv3=332748118;
const int N=1000010;
int n,q;
char s[N];

struct DMK
{
    int A,B,C,D,id;
    void init(){scanf("%d%d%d%d",&A,&B,&C,&D);id=1;}
    void get(int &l,int &r)
    {
        l=min(A,B);
        r=max(A,B);
        A=((A^id)+C)%n+1;
        B=((B^id)+D)%n+1;
        id++;
    }
} dmk;

struct Matrix
{
    int a[4][4];
    Matrix(){memset(a,0,sizeof(a));}
    Matrix operator * (const Matrix &b)
    {
        Matrix c;
        for(int i=0;i<4;i++)
            for(int k=0;k<4;k++)
                for(int j=0;j<4;j++)
                    c.a[i][j]=(c.a[i][j]+1ll*a[i][k]*b.a[k][j])%ha;
        return c;
    }
    int getans(){return (1ll*a[3][0]+a[3][1]+a[3][2]+a[3][3])%ha;}
    void sete(){a[0][0]=a[1][1]=a[2][2]=a[3][3]=1;}
    void set0(){a[0][0]=a[0][3]=a[1][0]=a[1][1]=a[1][3]=a[2][0]=a[2][2]=a[2][3]=a[3][0]=a[3][1]=a[3][2]=1;a[3][3]=2;}
    void set1(){a[0][0]=a[1][0]=a[1][1]=a[2][0]=a[2][2]=a[3][0]=a[3][1]=a[3][2]=a[3][3]=1;}
    void set0inv(){a[0][1]=a[0][2]=a[1][1]=a[2][2]=a[3][0]=a[3][3]=1;a[0][3]=a[1][0]=a[2][0]=a[3][1]=a[3][2]=ha-1;}
    void set1inv(){a[0][0]=a[1][1]=a[2][2]=a[3][0]=a[3][3]=1;a[1][0]=a[2][0]=a[3][1]=a[3][2]=ha-1;}
} mat[N],imat[N];

int query()
{
    int l,r;
    dmk.get(l,r);
    Matrix a=imat[l]*mat[r];
    return a.getans();
}

int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    dmk.init();
    mat[1].sete();
    imat[1].sete();
    for(int i=2;i<=n;i++)
    {
        if(s[i-1]=='0') mat[i].set0(),imat[i].set0inv();
        else mat[i].set1(),imat[i].set1inv();
        Matrix tmp=mat[i]*imat[i];
        mat[i]=mat[i-1]*mat[i];
        imat[i]=imat[i]*imat[i-1];
    }
    int ans=0;
    while(q--) ans^=query();
    printf("%d\n",ans);
    return 0;
}
