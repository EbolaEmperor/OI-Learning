#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
int n,a,b;
int c1,c2,c3,c4;
int ans1,ans2,ans3,ans4;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    bool rev=0;
    scanf("%d%d%d",&n,&a,&b);
    if(b<a) swap(a,b),rev=1; //钦定a比b小
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        x%=a+b;
        if(x<a) c1++;
        if(x>=a&&x<b) c2++;
        if(x>=b&&x<2*a) c3++;
        if(x>=2*a&&x>=b) c4++;
    }
    ans1=1ll*(Pow(2,c2)-1)*Pow(2,n-c2)%ha; //选至少一个２类，持a者必胜．以下讨论排除２类
    if(c3) ans3=ans4=1ll*Pow(2,c3-1)*Pow(2,c1)%ha;else ans4=Pow(2,c1); //当只选１类和３类时，先后手必胜只与３类的奇偶性有关
    if(c4>=2) ans1=(ans1+1ll*(Pow(2,c4)-c4-1)*Pow(2,c1+c3))%ha; //选至少两个４类时，持a者必胜
    if(c4>=1) ans3=(ans3+1ll*c4*(c3?Pow(2,c3-1):1)%ha*Pow(2,c1))%ha; //选一个４类，且选了偶数个３类时，先手必胜
    if(c4>=1&&c3) ans1=(ans1+1ll*c4*Pow(2,c3-1)%ha*Pow(2,c1))%ha; //选一个４类，且选了奇数个３类时，持a者必胜
    if(rev) swap(ans1,ans2);
    printf("%d %d %d %d\n",ans1,ans2,ans3,ans4);
    return 0;
}