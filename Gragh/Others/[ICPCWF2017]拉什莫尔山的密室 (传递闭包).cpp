#include<bits/stdc++.h>
using namespace std;

const int N=55;
bool G[N][N];
char s1[N],s2[N];

int rc()
{
    char c=getchar();
    while(c<'a'||c>'z') c=getchar();
    return c-'a';
}

bool check()
{
    int len=strlen(s1);
    if(strlen(s2)!=len) return 0;
    for(int i=0;i<len;i++)
        if(!G[s1[i]-'a'][s2[i]-'a']) return 0;
    return 1;
}

int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        int u=rc(),v=rc();
        G[u][v]=1;
    }
    for(int i=0;i<26;i++) G[i][i]=1;
    for(int k=0;k<26;k++)
        for(int i=0;i<26;i++)
            for(int j=0;j<26;j++)
                G[i][j]|=(G[i][k]&&G[k][j]);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%s",s1,s2);
        puts(check()?"yes":"no");
    }
    return 0;
}