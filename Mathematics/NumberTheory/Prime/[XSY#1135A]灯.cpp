#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
int prm[N],tot=0;
bool mark[N];

void Init(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!mark[i]) prm[++tot]=i;
        for(int j=1;j<=tot&&i*prm[j]<=n;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
}

int main()
{
    int n;cin>>n;Init(n);
    printf("%d %d\n",tot,n<=16?n-1:n);
    if(n<=16) for(int i=1;i<=tot;i++) puts("1");
    else if(n>=26&&n<=34)
    {
        for(int i=1;i<=tot;i++)
        {
            if(prm[i]==5) puts("13");
            else if(prm[i]==7||prm[i]==17) puts("19");
            else if(prm[i]==11) puts("17");
            else puts("1");
        }
    }
    else
    {
        int t=1,x=0,y=0;
        while(prm[t]*prm[t]<n) t++;
        for(int i=t;i<=tot;i++)
            for(int j=i+1;prm[i]+prm[j]<n;j++)
                if(prm[j]%prm[i]==1){x=i;y=j;goto falun;}
        falun: for(int i=1;i<=tot;i++)
        {
            if(i==x) printf("%d\n",prm[i]+2);
            else if(i==y) printf("%d\n",prm[x]+prm[y]+1);
            else puts("1");
        }
    }
    return 0;
}