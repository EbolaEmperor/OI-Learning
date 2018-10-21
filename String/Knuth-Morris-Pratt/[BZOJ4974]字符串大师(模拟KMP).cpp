#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=100010;
int per[N],n;
char ans[N];
bool vis[30];

int main()
{
    n=read();
    for(int i=0;i<n;i++) per[i]=read();
    ans[0]='a';
    for(int i=1;i<n;i++)
    {
        if(per[i]<i+1) ans[i]=ans[i%per[i]];
        else
        {
            int t=i-1;
            memset(vis,0,sizeof(vis));
            while(t+1!=per[t])
            {
                vis[ans[t%per[t]+1]-'a']=1;
                t=t%per[t];
            }
            for(int j=1;j<26;j++)
                if(!vis[j]){ans[i]='a'+j;break;}
        }
    }
    ans[n]='\0';
    printf("%s\n",ans);
    return 0;
}