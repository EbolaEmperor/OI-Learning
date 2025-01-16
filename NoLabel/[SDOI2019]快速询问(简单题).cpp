#include<bits/stdc++.h>
using namespace std;

const int ha=10000019;
const int N=100010;
struct Qry{int ty,p,x;} qry[N];
map<int,int> val;
int n,q,t,a[N],b[N];
int add=0,mul=1,mdf=0,sum=0;
int inv[10000030];

int main()
{
    inv[1]=1;
    for(int i=2;i<ha;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&qry[i].ty);
        if(qry[i].ty==6) continue;
        if(qry[i].ty==1) scanf("%d",&qry[i].p);
        scanf("%d",&qry[i].x);
        if(qry[i].ty<5) ((qry[i].x%=ha)+=ha)%=ha;
        if(qry[i].ty==3&&qry[i].x==0) qry[i].ty=4;
    }
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
        scanf("%d%d",a+i,b+i);
    int ans=0;
    for(int i=1;i<=t;i++)
        for(int j=1;j<=q;j++)
        {
            int id=(a[i]+1ll*j*b[i])%q+1;
            int ty=qry[id].ty,p=qry[id].p,x=qry[id].x;
            if(ty==1)
            {
                x=1ll*(x-add+ha)*inv[mul]%ha;
                if(val.count(p)) sum=(sum-val[p]+ha)%ha;
                sum=(sum+(val[p]=x))%ha;
            }
            if(ty==2) add=(add+x)%ha;
            if(ty==3) add=1ll*add*x%ha,mul=1ll*mul*x%ha;
            if(ty==4) add=0,mul=1,mdf=x,val.clear(),sum=0;
            if(ty==5) ans=(ans+1ll*(val.count(x)?val[x]:mdf)*mul+add)%ha;
            if(ty==6) ans=(ans+1ll*mul*sum+1ll*add*val.size()+1ll*(1ll*mdf*mul+add)%ha*(n-val.size()))%ha;
        }
    cout<<ans<<endl;
    return 0;
}