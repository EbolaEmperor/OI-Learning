#include <bits/stdc++.h>
#define pdi pair<double, int>
using namespace std;

const int M = 16, N = 36;
int C[M][M];
int cnt[M], myFrd[M], n, m, k;
// frd2myFrd[i]: 原编号为 i 的朋友在 myFrd 里是几号
int frd2myFrd[N];
// f[S][i]: 当前已访问 S 里的朋友，位于 i 的主页，接下来遍历成功的概率
//          这里的 S 与 i 都是指 myFrd (my friends) 的编号，不是原始编号
double f[1 << M][M];
// isFrd[i][j]: myFrd[i] 与 myFrd[j] 是否为朋友
bool isFrd[M][M];

void read(){
    // freopen("friend.in", "r", stdin);
    // freopen("friend.out", "w", stdout);
    scanf("%d%d", &n ,&k);
    memset(frd2myFrd, -1, sizeof(frd2myFrd));
    frd2myFrd[0] = 0;
    static int tmpcnt[N];
    for(int i = 0; i < n; i++){
        scanf("%d", tmpcnt + i);
        for(int j = 0, x; j < tmpcnt[i]; j++){
            scanf("%d", &x); --x;
            if(!i){
                myFrd[j] = x;
                frd2myFrd[x] = j + 1;
                isFrd[0][j + 1] = true;
            } else if(frd2myFrd[i] != -1 && frd2myFrd[x] != -1) {
                isFrd[frd2myFrd[i]][frd2myFrd[x]] = true;
            }
        }
    }
    m = cnt[0] = tmpcnt[0];
    for(int i = 0; i < m; i++)
        cnt[i + 1] = tmpcnt[myFrd[i]];
    // for(int i = 0; i <= m; i++)
    //     cout << cnt[i] << endl;
}

void initC(){
    for(int i = 0; i < M; i++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
}

void doDP(int S, int i){
    // 现在已经访问了 S 里的朋友，位于 myFrd[i] 的主页
    // 考虑下一个去 myFrd[j] 的主页
    vector<double> nxtFrd;
    for(int j = 1; j <= m; j++)
        if(!(S >> (j - 1) & 1) && isFrd[i][j])
            nxtFrd.push_back(f[S | (1 << (j - 1))][j]);
    if(nxtFrd.empty()) return;
    sort(nxtFrd.begin(), nxtFrd.end(), greater<double>());
    if(cnt[i] <= k) // 朋友比 k 少，所有朋友都会展示在列表里，选继续成功概率最大的走进去
        f[S][i] = nxtFrd[0];
    else {
        // 否则，多个可访问朋友同时出现时，优先选继续成功概率大的
        // double check = 0;
        for(int rk = 0; rk < nxtFrd.size(); rk++){
            // 枚举选哪个 nxtFrd。对每个排名 rk，选 nxtFrd[rk] 充要条件是： 
            //      nxtFrd[0...rk-1] 都不出现，且 nxtFrd[rk] 出现
            if(cnt[i] - rk < k) break; // 剩下的不够凑成 k 个了
            double prob = (double) C[cnt[i] - rk - 1][k - 1] / C[cnt[i]][k];
            // check += prob;
            f[S][i] += prob * nxtFrd[rk];
        }
        // assert(fabs(check - 1.0) < 1e-14 || 
        //        fabs((1 - check) - (double) C[cnt[i] - nxtFrd.size()][k] / C[cnt[i]][k]) < 1e-14);
    }
}

double dp(){
    for(int i = 0; i < m; i++)
        f[(1 << m) - 1][i + 1] = 1.0;
    for(int S = (1 << m) - 2; S >= 0; S--)
        for(int i = 1; i <= m; i++)
            if(S >> (i - 1) & 1) doDP(S, i);
    doDP(0, 0);
    return f[0][0];
}

int main(){
    read();
    initC();
    printf("%.12lf\n", dp());
    return 0;
}