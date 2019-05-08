#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=1e9+7;
struct Matrix
{
    int a[26][26];
    Matrix(){memset(a,0,sizeof(a));}
    Matrix operator * (const Matrix &b)
    {
        Matrix c;
        for(int i=0;i<26;i++)
            for(int k=0;k<26;k++)
                for(int j=0;j<26;j++)
                    c.a[i][j]=(c.a[i][j]+1ll*a[i][k]*b.a[k][j])%ha;
        return c;
    }
    friend Matrix operator ^ (Matrix a,LL b)
    {
        Matrix ans;
        for(int i=0;i<26;i++)
            ans.a[i][i]=1;
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
} A;
char s[10010];
LL n;

int main()
{
    scanf("%lld%s",&n,s+1);
    int len=strlen(s+1);
    for(int i=1;i<len;i++)
        A.a[s[i]-'a'][s[i+1]-'a']=1;
    for(int i=0;i<26;i++)
        for(int j=0;j<26;j++)
            A.a[i][j]^=1;
    A=A^(n-1);
    int ans=0;
    for(int i=0;i<26;i++)
        for(int j=0;j<26;j++)
            ans=(ans+A.a[i][j])%ha;
    cout<<ans<<endl;
    return 0;
}