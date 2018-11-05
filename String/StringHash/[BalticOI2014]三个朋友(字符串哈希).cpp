#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=2000010;
ULL suf[N],base[N],back,front;
char s[N],*ans;
int n,cnt=0;

void check1()
{
    back=0;
    for(int i=n/2+2;i<=n;i++)
        back=back*233+s[i];
    for(int i=n/2+1,x=0;i>=1;i--,x++)
        suf[i]=base[x]*s[i]+suf[i+1];
    ULL pre=0;
    for(int i=1;i<=n/2+1;i++)
    {
        ULL t=pre*base[n/2+1-i]+suf[i+1];
        if(t==back) cnt=1,ans=s+n/2+2;
        pre=pre*233+s[i];
    }
}

bool check2()
{
    front=0;int val=2;
    for(int i=1;i<=n/2;i++)
        front=front*233+s[i];
    if(front==back) val=1;
    for(int i=n,x=0;i>=n/2+2;i--,x++)
        suf[i]=base[x]*s[i]+suf[i+1];
    ULL pre=s[n/2+1];
    for(int i=n/2+2;i<=n;i++)
    {
        ULL t=pre*base[n-i]+suf[i+1];
        if(t==front) cnt|=val,ans=s+1;
        pre=pre*233+s[i];
    }
    if(cnt==3) return 1;
    if(ans==s+1) s[n/2+1]='\0';
    return 0;
}

int main()
{
    scanf("%d",&n);
    if(~n&1) return puts("NOT POSSIBLE"),0;
    base[0]=1;
    for(int i=1;i<=n;i++)
        base[i]=base[i-1]*233;
    scanf("%s",s+1);
    check1();
    if(check2()) return puts("NOT UNIQUE"),0;
    if(cnt) printf("%s\n",ans);
    else puts("NOT POSSIBLE");
    return 0;
}