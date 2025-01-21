// 注：这份代码包括了 3 档部分分，如果想看正解，直接看 alltask 即可
#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int n, k, cnt[N][N], tot[N], tots[N];
double ans[N];

// O(n * 2^n) 暴力枚举
void subtask1(){
    static int tmpcnt[N];
    for(int s = 1; s < (1 << n); s++){
        memset(tmpcnt, 0, sizeof(tmpcnt));
        int sum = 0;
        for(int i = 0; i < n; i++) if((s >> i) & 1)
            for(int j = 0; j < k; j++)
                tmpcnt[j] += cnt[i][j], sum += cnt[i][j];
        if(!sum) continue;
        for(int j = 0; j < k; j++)
            ans[j] += (double) tmpcnt[j] / sum / ((1 << n) - 1);
    }
}

// 针对 k=2 的 dp
// 设 f[i][m] 表示在前 i 个盒子里选，考虑所有选了恰好 m 个球的方案，这些方案选的 0 色球的数量之和
//    g[i][m] 表示在前 i 个盒子里选，选了恰好 m 个球的方案数量
// 转移方程类似 01 背包，不难发现第一维可以压掉
// 则答案就是 ans = sum( f[n-1][m] / m / ((1 << n) - 1) )
void subtask2(){
    static double f[N * 400];
    static long long g[N * 400];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    g[0] = g[tot[0]] = 1;
    f[tot[0]] = cnt[0][0];
    for(int i = 1; i < n; i++)
        for(int m = (i + 1) * 400; m >= tot[i]; m--){
            f[m] += f[m - tot[i]] + 1.0 * cnt[i][0] * g[m - tot[i]];
            g[m] += g[m - tot[i]];
        }
    for(int m = 1; m <= n * 400; m++)
        ans[0] += f[m] / m / ((1ll << n) - 1);
    ans[1] = 1.0 - ans[0];
}

// 这是一个 O(n^2 * k^2 * maxC) 的做法，但跑得飞快
// 把 subtask2 的做法拓展一下即可，f 增加一维，记录这些方案选的每一种颜色球数量之和
void subtask3(){
    static double f[N * N * 200][N];
    static long long g[N * N * 200];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    g[0] = g[tot[0]] = 1;
    for(int j = 0; j < k; j++)
        f[tot[0]][j] = cnt[0][j];
    for(int i = 1; i < n; i++)
        for(int m = tots[i]; m >= tot[i]; m--){
            for(int j = 0; j < k; j++)
                f[m][j] += f[m - tot[i]][j] + 1.0 * cnt[i][j] * g[m - tot[i]];
            g[m] += g[m - tot[i]];
        }
    for(int m = 1; m <= tots[n - 1]; m++)
        for(int j = 0; j < k; j++)
            ans[j] += f[m][j] / m / ((1ll << n) - 1);
}

// 这是 O(n^2 * k * maxC) 的正解
// 注意到我们可以把选球拆成两步：先决定选个盒子里的球，再决定选择这个盒子里哪个颜色的球
// 于是我们只要知道选第 i 个盒子里选球的概率。所以之前的 f 其实是没意义的，我们只需要记录 g 即可
// 设 h[i][m] 表示在不选 i 个盒子的前提下，选了恰好 m 个球的方案数量
// 可以推出：h[i][m] = g[m] - h[i][m-tot[i]]
//         这里 h[i][m-tot[i]] 的意思是钦定 i 号盒子必选，然后在剩下的盒子里选 m-tot[i] 个球的方案数
//         用总的 g[m] 减一下，就得到了不选 i 号盒子的方案数
//         其实就是退背包
// 对于一个选了 m 个球且 i 号盒子必选的方案，最终选择 i 号盒子里的球的概率是 tot[i] / m，
// 而这些方案的个数是 h[i][m-tot[i]]
void alltask(){
    static long long g[N * N * 200], h[N * N * 200];
    const long long M = (1ll << n) - 1;
    memset(g, 0, sizeof(g));
    g[0] = g[tot[0]] = 1;
    for(int i = 1; i < n; i++)
        for(int m = tots[i]; m >= tot[i]; m--)
            g[m] += g[m - tot[i]];
    for(int i = 0; i < n; i++){
        double prob = 0; // 最终选的球来自 i 号盒子的概率
        for(int m = 0; m <= tots[n - 1]; m++){
            h[m] = g[m];
            if(m >= tot[i]){
                h[m] -= h[m - tot[i]];
                prob += (double) tot[i] / m * h[m - tot[i]] / M;
            }
        }
        for(int j = 0; j < k; j++)
            ans[j] += prob * cnt[i][j] / tot[i];
    }
}

int main(){
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++)
            cin >> cnt[i][j], tot[i] += cnt[i][j];
        tots[i] = tot[i];
        if(i) tots[i] += tots[i - 1];
    }
    // if((1ll << n) * n * k <= 1e8) subtask1();
    // else if(k == 2) subtask2();
    // else subtask3();
    alltask();
    cout << setprecision(12);
    for(int j = 0; j < k; j++)
        cout << ans[j] << " ";
    cout << endl;
    return 0;
}