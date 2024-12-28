#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
long long t[2], f[N], p[2], s;

// 这题可以看作背包，但物品是你构造的。一个物品 = 若干次单击 + 最后一次双炮合击。
// 物品的重量是攻击的伤害，价值是消耗的时间。要求总重量至少为 h，最小化总价值。
// 详细题解见 Lecture 13 - selected DP problems
void update(long long h, int c){
    for(int j = 1; j * (p[c] - s) <= h; j++){
        auto tt = j * t[c];
        auto other = j * t[c] / t[c^1] - 1;
        if(other < 0) continue;
        auto x = (j - 1) * (p[c] - s) + other * (p[c^1] - s) + (p[c] + p[c^1] - s);
        x = min(x, h);
        f[h] = min(f[h], f[h-x] + tt);
    }
}

int main(){
    int h;
    cin >> p[0] >> t[0] >> p[1] >> t[1] >> h >> s;
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for(int i = 1; i <= h; i++){
        update(i, 0);
        update(i, 1);
    }
    auto ans = f[h];
    ans = min(ans, ((h - 1) / (p[0] - s) + 1) * t[0]);
    ans = min(ans, ((h - 1) / (p[1] - s) + 1) * t[1]);
    cout << ans << endl;
    return 0;
}