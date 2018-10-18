#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

char falun[10000];
int a[10],val[10],n,ans,len;
int stn[110],topn=0,topo=0;
char sto[110];

void gao_or()
{
    while(sto[topo]=='|')
    {
        bool tmp=(stn[topn-1]||stn[topn]);
        stn[--topn]=tmp;topo--;
    }
}

void gao_and()
{
    while(sto[topo]=='&')
    {
        bool tmp=(stn[topn-1]&&stn[topn]);
        stn[--topn]=tmp;topo--;
    }
}

bool check()
{
    topo=topn=0;
    for(int i=1;i<=len;i++)
    {
        char dafa=falun[i];
        switch(dafa)
        {
            case '(': sto[++topo]=dafa;break;
            case '&': sto[++topo]=dafa;break;
            case '<': sto[++topo]=dafa;break;
            case '|': gao_or();sto[++topo]=dafa;break;
            case ')': gao_or();topo--;gao_and();break;
            default:
                stn[++topn]=val[dafa-'a'+1];
                if(sto[topo]!='<') break;
                bool tmp=(stn[topn-1]<stn[topn]);
                stn[--topn]=tmp;
                topo--;gao_and();
        }
    }
    return stn[topn];
}

int calc(int p,int m)
{
    if(p>7) return check();
    int ans=0;
    for(int i=0;i<m;i++)
        val[p]=i,ans+=calc(p+1,m);
    return ans;
}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int Lagrange(int x)
{
    int ans=0;
    for(int i=1;i<=8;i++)
    {
        int prod1=a[i],prod2=1;
        for(int j=1;j<=8;j++)
        {
            if(i==j) continue;
            prod1=1ll*prod1*(x-j)%ha;
            prod2=1ll*prod2*(i-j)%ha;
        }
        prod1=(prod1+ha)%ha;prod2=(prod2+ha)%ha;
        ans=(ans+1ll*prod1*Pow(prod2,ha-2))%ha;
    }
    return ans;
}

int main()
{
    char c;
    falun[len=1]='(';
    do{c=getchar();if(c!=' ')falun[++len]=c;}while(c!='\n');
    falun[len]=')';
    for(int i=1;i<=8;i++) a[i]=calc(1,i);
    cin>>n;
    cout<<Lagrange(n)<<endl;
    return 0;
}