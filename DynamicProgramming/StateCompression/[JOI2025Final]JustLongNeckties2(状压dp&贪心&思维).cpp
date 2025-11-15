#include <bits/stdc++.h>
using namespace std;

const int N = 5e6 + 5;
const int V = 21, S = 1 << V;
int n, a[N];
int f1[N][V]; // f1[i][x]: [i,n] 里第一个 =x 的位置
int f2[N][V]; // f2[i][x]: [i,n] 里第一个满足 (a[j], a[j+1]) = (a[i], x) 的位置 j
int dp[S]; // 当前手上的数字集合为 S，最后能响应到哪个观众
int highbit[S], siz[S], go[S][V];

inline void upmax(int &x, int y) {
    if (y > x) x = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
    }

    for (int x = 0; x < V; x++) f1[n+1][x] = f2[n+1][x] = n+1;
    for (int i = n; i >= 0; i--) {
        memcpy(f1[i], f1[i+1], sizeof(f1[i]));
        if (i) f1[i][a[i]] = i;
    }
    for (int i = n; i >= 1; i--) {
        memcpy(f2[i], f2[f1[i+1][a[i]]], sizeof(f2[i]));
        if (i < n) f2[i][a[i+1]] = i;
    }

    // 一个显然的贪心想法：手上的数字肯定是越小越好
    // 当你需要修改数字去相应一个观众 Ai 的时候，肯定是选择手上 < Ai 且最大的那个数字去改；如果没有，那就加一个
    // 所以可以预处理一个转移 go[S][x]，表示当前手上数字集合为 S，响应了观众 Ai=x 之后，手上的数字集合变成多少
    highbit[1] = 1;
    for (int s = 0; s < S; s++) {
        siz[s] = siz[s >> 1] + (s & 1);
        if (s > 1) highbit[s] = highbit[s >> 1] << 1;
        for (int x = 0; x < V; x++)
            if (s >> x & 1) go[s][x] = s;
            else {
                int tmp = ((1 << x + 1) - 1) & s;
                go[s][x] = s ^ highbit[tmp] ^ (1 << x); 
            }
    }

    // 保持手上的数字不变，尽可能去拖延时间，拖到后两个都无法响应了，再改变手上的数字去相应观众
    //      如果你不改手上的数字，响应到了第 i 个观众；
    //      相比你增大了某个数字，响应到了第 i 个观众，显然前者更优。
    //      你在前面响应更多的观众，并不会对你响应第 i 个之后的观众带来什么好处
    int ans = V;
    for (int s = 0; s < S; s++) {
        // 找到 dp[S] 之后第一个位置 i，满足 {a[i], a[i+1]} notin S
        // 为此，枚举 a[i]=x， a[i+1]=y，并通过预处理的 f2 找到这样的 i
        int nxtpos = n + 1;
        for (int x = 0; x < V; x++) if (!(s >> x & 1))
            for (int y = 0; y < V; y++) if (!(s >> y & 1))
                nxtpos = min(nxtpos, f2[f1[dp[s]+1][x]][y]);
        dp[s] = nxtpos - 1;
        // 尝试响应下一个或者下下一个观众，进行转移
        if (nxtpos <= n) upmax(dp[go[s][a[nxtpos]]], nxtpos);
        if (nxtpos < n) upmax(dp[go[s][a[nxtpos + 1]]], nxtpos + 1);
        if (dp[s] >= n - 1) ans = min(ans, siz[s]);
    }
    cout << ans << endl;

    return 0;
}