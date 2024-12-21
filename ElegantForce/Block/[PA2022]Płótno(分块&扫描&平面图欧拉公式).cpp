// 注：这份代码来自洛谷题解，原题解链接：https://www.luogu.com.cn/article/d7rqyd40
// 我添加了一些注释，以便理解
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int b=1400;
const int itc=200000;

int n,k;
int col[2][100005];
int tag[150],cnt[150][400005],cur[200005];
ll ans[15];
vector<int> adj[200005];

inline void add(int pos,int val)
{
    // 给 val(1..pos, r) 加上 val，r 是主函数里的 i，即当前扫描到的颜色右端点
    for(int i=1;;i++)
    {
        if(pos<=i*b)
        {
            // 如果 pos 在块 i 里，那么暴力更新块里的每个 cur，并更新 cnt
            for(int j=(i-1)*b+1;j<=pos;j++)
            {
                cnt[i][cur[j]]--;
                cur[j]+=val;
                cnt[i][cur[j]]++;
            }

            break;
        }

        // 如果 pos 不在块 i 里，那么直接更新块的 lazy tag
        tag[i]+=val;
    }
}

inline void sol(int sum)
{
    for(int i=1;;i++)
    {
        // 统计这个块里 =sum 的个数，由于有 lazy tag，所以要减去 tag，再加上防越界的位移量 itc
        ans[sum]+=cnt[i][itc+sum-tag[i]];

        if(n+n<=i*b)
            break;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    
    cin>>n>>k;

    for(int i=1;i<=n;i++)
        cin>>col[0][i];

    for(int i=1;i<=n;i++)
        cin>>col[1][i];

    for(int i=1;i<=n;i++)
    {
        // 考虑计算 V+E-S
        // V 就是在扫到 r 时，令 val(1..r,r) += 1
        // E 就是，考虑 1*2 块里的两个数 x1<x2，扫到 x2 时时，令 val(1..x1,x2) += 1
        // S 就是，考虑 2*2 块里的四个数 x1<x2<x3<x4，扫到 x4 时，令 val(1..x1,x4) += 1
        adj[col[0][i]].push_back(col[0][i]);
        adj[col[1][i]].push_back(col[1][i]);
        adj[max(col[0][i],col[1][i])].push_back(-min(col[0][i],col[1][i]));
        adj[max(col[0][i],col[0][i%n+1])].push_back(-min(col[0][i],col[0][i%n+1]));
        adj[max(col[1][i],col[1][i%n+1])].push_back(-min(col[1][i],col[1][i%n+1]));
        adj[max(max(col[0][i],col[0][i%n+1]),max(col[1][i],col[1][i%n+1]))].push_back(min(min(col[0][i],col[0][i%n+1]),min(col[1][i],col[1][i%n+1])));
    }

    for(int i=1;i<=n+n;i++)
    {
        // i 从左往右扫描，计算所有的 val(l,i)

        int id=(i-1)/b+1;
        // itc: 一个常数，防越界的位移量
        // tag[id]: 块 id 的 lazy 加法标记
        // cur[i]: val(i,i) 的值，初始化为 0，但为了 lazy 处理，需要减去块 lazy tag
        cur[i]=itc-tag[id];
        // cnt[id][x]: id 块中 x 的个数
        cnt[id][cur[i]]++;

        for(int j=0;j<adj[i].size();j++)
        {
            // pos: 与颜色 i 相邻（上下相邻，或左右相邻，或在同一个 2*2 块里）的、编号比 i 小的颜色的位置
            // pos 带符号，正号表示正贡献，负号表示负贡献，对应 V+E-F 里的 E 和 F
            int pos=adj[i][j],coef;

            if(pos>0)
                coef=1;
            else
                pos=-pos,coef=-1;

            // val(1..pos,i) += coef
            add(pos,coef);
        }

        for(int j=0;j<=k;j++)
            // 统计所有的 val(l,i) 里有几个 =j 的
            sol(j);
    }

    ans[1]+=ans[0];

    for(int i=1;i<=k;i++)
        cout<<ans[i]<<' ';
    cout<<'\n';

    return 0;
}