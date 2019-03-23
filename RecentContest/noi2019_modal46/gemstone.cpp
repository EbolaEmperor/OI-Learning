#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=10000,M=N+5;
int tok[M],rin[M],cnt[M],q;

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}
inline void mns(int &x,const int &y){x=(x-y<0)?(x-y+ha):(x-y);}

void insert()
{
    int x;scanf("%d",&x);cnt[x]++;
    for(int i=N-x;i>=0;i--)
        add(tok[i+x],tok[i]);
    
    for(int i=N;i>max(N-x*(cnt[x]+1),-1);i--)
        rin[i]=rin[i]?(ha-rin[i]):0;
    for(int i=N-x*(cnt[x]+1);i>=0;i--)
        add(rin[i+x*(cnt[x]+1)],rin[i]),rin[i]=rin[i]?(ha-rin[i]):0;
    
    for(int i=0;i<=N-x*cnt[x];i++)
        rin[i]=rin[i]?(ha-rin[i]):0,mns(rin[i+x*cnt[x]],rin[i]);
    for(int i=max(N-x*cnt[x]+1,0);i<=N;i++)
        rin[i]=rin[i]?(ha-rin[i]):0;
}

void remove()
{
    int x;scanf("%d",&x);
    for(int i=0;i<=N-x;i++)
        mns(tok[i+x],tok[i]);
    
    for(int i=0;i<=N-x*(cnt[x]+1);i++)
        rin[i]=rin[i]?(ha-rin[i]):0,mns(rin[i+x*(cnt[x]+1)],rin[i]);
    for(int i=max(N-x*(cnt[x]+1)+1,0);i<=N;i++)
        rin[i]=rin[i]?(ha-rin[i]):0;
    
    for(int i=N;i>max(N-x*cnt[x],-1);i--)
        rin[i]=rin[i]?(ha-rin[i]):0;
    for(int i=N-x*cnt[x];i>=0;i--)
        add(rin[i+x*cnt[x]],rin[i]),rin[i]=rin[i]?(ha-rin[i]):0;
    cnt[x]--;
}

int main()
{
    scanf("%d",&q);
    char opt[5],name[15];
    tok[0]=rin[0]=1;
    while(q--)
    {
        scanf("%s",opt);
        if(opt[0]=='i') insert();
        if(opt[0]=='d') remove();
        if(opt[0]=='q')
        {
            int k;
            scanf("%s%d",name,&k);
            printf("%d\n",(name[0]=='T')?tok[k]:rin[k]);
        }
    }
    return 0;
}