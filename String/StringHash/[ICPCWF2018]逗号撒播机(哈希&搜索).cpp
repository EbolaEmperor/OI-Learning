#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
unordered_map<string,int> h;
vector<int> G[N];
int spt[N][2],cnt=0,idx=0,len;
string s[N];
char ss[N];
bool done[N][2];

int read()
{
    char c=getchar();len=0;
    while((c<'a'||c>'z')&&c!=EOF) c=getchar();
    if(c==EOF) return -1;
    while(c>='a'&&c<='z') ss[len++]=c,c=getchar();
    ss[len]='\0';s[++cnt]=ss;
    if(c==',') return 1;
    if(c=='.') return 2;
    return 0;
}

void Init()
{
    int spot,pre=0;
    while(~(spot=read()))
    {
        spt[cnt][0]=pre;
        spt[cnt][1]=spot;
        if(!h.count(s[cnt])) h[s[cnt]]=++idx;
        G[h[s[cnt]]].push_back(cnt);
        pre=spot;
    }
}

void dfs(int x,int d)
{
    if(done[x][d]) return;
    done[x][d]=1;
    for(int u : G[x])
    {
        if(spt[u][d]) continue;
        spt[u][d]=1;
        if(d==0&&u>1) dfs(h[s[u-1]],1);
        if(d==1&&u<cnt) dfs(h[s[u+1]],0);
    }
}

int main()
{
    Init();
    for(int i=1;i<=cnt;i++)
        for(int j=0;j<2;j++)
        {
            int x=h[s[i]];
            if(done[x][j]) continue;
            if(spt[i][j]==1) dfs(x,j);
        }
    ios::sync_with_stdio(0);
    for(int i=1;i<=cnt;i++)
    {
        cout<<s[i];
        if(spt[i][1]==1) cout<<",";
        if(spt[i][1]==2) cout<<".";
        if(i<cnt) cout<<" ";
    }
    cout<<endl;
    return 0;
}