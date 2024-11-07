#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int N = 16;
int les[N];
// les[p] 是一个二进制表示的集合，表示所有应该满足 ans[i] < ans[p] 的位置 i 们
int n, m;
int ans[N], pos[N];
LL rnk;

// 计算在固定了一些位置的前提下，剩余的合法方案数有多少
LL check(){
    static LL dp[1 << N];
    // dp[S] 表示将数字 0,1,...,|S|-1 放在位置集合 S 里的合法方案数
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int S = 0; S < (1<<n); S++){
        int k = __builtin_popcount(S);
        // 考虑将数字 k 放在位置 p
        for(int p = 0; p < n; p++){
            // 1. p not in S
            // 2. 强制要求 ans[i] < ans[p] 的位置 i 必须包含在 S 中，即 les[p] in S 
            // 3. 如果 ans[p] 已被固定，则必须是 k
            // 4. 如果 k 已经确定位置，则必须确定在 p 位置
            if( !(S >> p & 1) &&
                (les[p] & S) == les[p] &&
                (ans[p] == -1 || ans[p] == k) &&
                (pos[k] == -1 || pos[k] == p))
                dp[S | (1 << p)] += dp[S];
        }
    }
    return dp[(1 << n) - 1];
}

bool solve(){
    int cnt = 0;
    memset(ans, -1, sizeof(ans));
    memset(pos, -1, sizeof(pos));
    for(int i = 0; i < n; i++){
        // 尝试令 ans[i] = x
        for(int x = 0; x < n; x++){
            if(pos[x] != -1) continue;
            pos[x] = i; ans[i] = x;
            LL tmp = check();
            // 类似于在字典树上贪心向左走，只要左子树的合法方案数足够 rnk 个就往左；
            // 否则 rnk 减去左子树的方案数，往右边的子树继续尝试
            if(tmp >= rnk) {cnt++; break;}
            else rnk -= tmp;
            pos[x] = ans[i] = -1;
        }
        if(cnt != i + 1) return false;
    }
    return true;
}

int main(){
    cin >> n >> rnk >> m;
    rnk -= 2000;
    for(int i = 0, x, y; i < m; i++){
        cin >> x >> y;
        x--; y--;
        les[y] |= (1 << x);
    }
    if(!solve()) cout << "The times have changed" << endl;
    else {
        for(int i = 0; i < n; i++)
            cout << ans[i] + 1 << " ";
        cout << endl;
    }
    return 0;
}