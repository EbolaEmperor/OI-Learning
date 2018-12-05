#include<bits/stdc++.h>
using namespace std;

const int N=25;
char poker[N];
int cnt[N];
int n,ans=-1;
bool big=0;

void Init()
{
    for(int i=1;i<=n;i++)
    {
        char c=poker[i];
        if(isdigit(c)&&c>'2') cnt[c-'0']++;
        else if(c=='T') cnt[10]++;
        else if(c=='J') cnt[11]++;
        else if(c=='Q') cnt[12]++;
        else if(c=='K') cnt[13]++;
        else if(c=='A') cnt[14]++;
        else if(c=='2') cnt[15]++;
        else cnt[16]++;
        if(c=='W') big=1;
    }
}

void print(int c)
{
    if(c==100) puts("-1");
    else if(c<10) printf("%d\n",c);
    else if(c==10) puts("T");
    else if(c==11) puts("J");
    else if(c==12) puts("Q");
    else if(c==13) puts("K");
    else if(c==14) puts("A");
    else if(c==15) puts("2");
    else puts(big?"W":"w");
}

void dfs(int rest)
{
    // 顺子
    for(int i=3;i<=10;i++)
        for(int j=5;i+j-1<=14;j++)
        {
            bool flag=0;
            for(int k=i;k<i+j;k++)
                if(!cnt[k]) flag=1;
            if(flag) break;
            for(int k=i;k<i+j;k++) cnt[k]--;
            dfs(rest-j);
            for(int k=i;k<i+j;k++) cnt[k]++;
        }

    // 三带一
    for(int i=3,j;i<=16;i++)
        if(cnt[i]>=3)
        {
            cnt[i]-=3;
            for(j=3;j<=16;j++)
                if(cnt[j]==1){cnt[j]--;break;}
            dfs(j<=16?rest-4:rest-3);
            cnt[i]+=3;
            if(j<=16) cnt[j]++;
        }
    
    // 四带二
    for(int i=3,j;i<=16;i++)
        if(cnt[i]==4)
        {
            cnt[i]-=4;
            int flag=0;
            int fk[3],tt=0;
            for(int j=3;j<=16;j++)
                if(cnt[j]==1)
                {
                    cnt[j]--;
                    fk[++tt]=j;
                    if(++flag>=2)break;
                }
            if(flag<2)
                for(int j=3;j<=16;j++)
                    if(cnt[j])
                    {
                        cnt[j]--;
                        fk[++tt]=j;
                        break;
                    }
            dfs(rest-6);
            for(int j=1;j<=tt;j++) cnt[fk[j]]++;
            cnt[i]+=4;
        }
    
    // 对子
    for(int i=3;i<=16;i++)
        if(cnt[i]>=2)
        {
            cnt[i]-=2;
            dfs(rest-2);
            cnt[i]+=2;
        }

    // 全都是单牌了
    bool finished=1;int mn=0,mns=0;
    for(int i=3;i<=16;i++)
    {
        if(cnt[i]>1) finished=0;
        if(cnt[i]==1&&!mn) mn=i;
        else if(cnt[i]==1&&!mns) mns=i;
    }
    if(finished){ans=max(ans,mns?mns:100);return;}
}

int main()
{
    scanf("%d%s",&n,poker+1);
    Init();dfs(n);
    print(ans);
    return 0;
}