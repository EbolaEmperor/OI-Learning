#include <bits/stdc++.h>
using namespace std;

// 我们求有多少个不同的 “代表数”
// “代表数” 是指：不能通过交换操作让字典序变小的数
// 每个 “代表数” 代表了一个等价类

const int ha = 998244353;
const int N = 1024;
bool swp[10][10];
int trans[N][10];
// trans[S][c]: 若 a[i] 不能填 S 中的数，令 a[i]=c 之后，
//              a[i+1] 不能填哪些数
int f[2][N];
// f[i][S]: 考虑前 i 位，a[i] 不能填 S 中的数，此时有几个 “代表数”
//          用滚动数组优化空间

inline void add(int &x, const int &y){
    x = (x + y >= ha) ? x + y - ha : x + y;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v; i <= m; ++i){
        scanf("%d%d", &u, &v);
        swp[u][v] = swp[v][u] = 1;
    }
    for(int s = 0; s < 1<<10; ++s)
        for(int c = 0; c < 10; ++c){
            if(s >> c & 1) continue;
            for(int v = 0; v < 10; ++v)
                // 如果可以交换 (c,v) 使得字典序直接变小，
                // 或者本来 a[i] 是禁止 v 的，但在令 a[i+1]=v 之后可以交换 (c,v) 把 v 放到 a[i]，
                // 那 a[i+1] 就不能放 v
                //
                // Remark: 如果交换 (c,v) 再继续往前交换可以让字典序间接变小，
                //         那 s 一定包含了 “禁止v” 这一信息
                if(swp[c][v] && (v < c || (s >> v & 1)))
                    trans[s][c] |= 1 << v;
        }
    int p = 0;
    f[p][0] = 1;
    for(int i = 0; i < n; ++i, p ^= 1){
        memset(f[p^1], 0, sizeof(f[p^1]));
        for(int s = 0; s < 1<<10; ++s){
            if(!f[p][s]) continue;
            for(int c = 0; c < 10; ++c)
                if(!(s >> c & 1)) add(f[p^1][trans[s][c]], f[p][s]);
        }
    }
    int ans = 0;
    for(int s = 0; s < 1<<10; ++s) add(ans, f[p][s]);
    cout << ans << endl;
    return 0;
}

// idea: 把这个题的数字范围缩小到 5，可以出成矩阵快速幂的题目，可以把 n 开到非常大