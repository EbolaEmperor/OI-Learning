#include<bits/stdc++.h>
using namespace std;

const int N=100010,D=25010;
int a[N],n,T;
bool cann[D],done[D];

void gao(int x)
{
    cann[x]=1;
    for(int k=0;k<=a[n];k++)
    {
        if(!cann[k]) continue;
        if(done[k]) continue;
        for(int i=1;k+x*i<=a[n];i++)
        {
            if(done[k+x*i]) break;
            cann[k+x*i]=1;
            done[k+x*i]=1;
        }
    }
}

int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        int tot=0;
        memset(cann,0,sizeof(cann));
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++)
        {
            if(cann[a[i]]) continue;
            memset(done,0,sizeof(done));
            gao(a[i]);tot++;
        }
        cout<<tot<<endl;
    }
    return 0;
}
