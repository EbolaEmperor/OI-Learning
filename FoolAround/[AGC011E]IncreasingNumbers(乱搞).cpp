#include<bits/stdc++.h>
using namespace std;

const int N=501010;
char s[N];

struct Bigint
{
    int a[N],n;
    int& operator [] (const int &x){return a[x];}
    Bigint(){memset(a,0,sizeof(a));n=0;}
    Bigint(char *s){n=strlen(s);for(int i=0;i<n;i++)a[i]=s[n-i-1]-'0';}
    void carry()
    {
        for(int i=0;i<n;i++)
        {
            if(a[i]<=9) continue;
            a[i+1]+=a[i]/10;
            a[i]%=10;
            if(i==n-1) n++;
        }
    }
    Bigint& operator *= (int x){for(int i=0;i<n;i++)a[i]*=x;carry();return *this;}
    int get(){int res=0;for(int i=0;i<n;i++)res+=a[i];return res;}
    void gao(int &sum)
    {
        a[0]+=9;sum+=9;
        for(int i=0;a[i]>9;i++)
        {
            sum-=a[i];sum-=a[i+1];
            a[i+1]+=a[i]/10;a[i]%=10;
            sum+=a[i];sum+=a[i+1];
            if(i==n-1) n++;
        }
    }
} A;

int main()
{
    scanf("%s",s);
    A=s;A*=9;
    int sum=A.get(),k;
    for(k=1;true;k++)
    {
        A.gao(sum);
        if(sum<=9*k&&sum%9==0) break;
    }
    cout<<k<<endl;
    return 0;
}