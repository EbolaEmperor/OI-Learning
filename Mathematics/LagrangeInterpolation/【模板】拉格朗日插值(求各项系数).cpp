#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=5010;
int a[N],arrx[N],arry[N],n;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

struct Poly
{
    vector<int> a;
    Poly(int x=0){a.resize(x);}
    int size(){return a.size();}
    int& operator [] (const int &x){return a[x];}

    Poly operator * (Poly &B)
    {
        Poly C(size()+B.size()-1);
        if(!size()) return B;
        for(int i=0;i<size();i++)
            for(int j=0;j<B.size();j++)
                C[i+j]=(C[i+j]+1ll*a[i]*B[j])%ha;
        return C;
    }

    Poly operator / (Poly &B)
    {
        Poly C=*this;
        int x=0,y=Pow(B[0],ha-2);
        for(int i=0;i<size();i++)
        {
            int z=(C[i]-x+ha)%ha;
            C[i]=x;x=1ll*z*y%ha;
        }
        for(int i=0;i<size()-1;i++)
            C[i]=C[i+1];
        C.a.pop_back();
        return C;
    }
};

void Lagrange()
{
    Poly S;
    for(int i=1;i<=n;i++)
    {
        Poly tmp(2);
        tmp[0]=ha-arrx[i];tmp[1]=1;
        S=S*tmp;
    }
    for(int i=1;i<=n;i++)
    {
        Poly tmp(2);
        tmp[0]=ha-arrx[i];tmp[1]=1;
        Poly erator=S/tmp;
        Poly tttt=erator*tmp;
        int minator=1;
        for(int j=1;j<=n;j++)
            if(i!=j) minator=1ll*minator*(arrx[i]-arrx[j])%ha;
        minator=Pow((minator+ha)%ha,ha-2);
        int k=1ll*minator*arry[i]%ha;
        for(int j=0;j<erator.size();j++)
            a[j]=(a[j]+1ll*erator[j]*k)%ha;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",arrx+i,arry+i);
    Lagrange();
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    return 0;
}