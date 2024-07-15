#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha = 998244353;
const int N = 400010;
int n, col[N];
int rht[N];
LL rndval[N];
mt19937_64 rnd(19260817);

int check(int l, int r){
    int cnt = 0;
    while(l <= r){
        if(rht[l]) l = rht[l] + 1;
        else ++cnt, ++l;
    }
    return cnt;
}

void work(){
    scanf("%d", &n);
    for(int i = 1; i <= 2 * n; ++i) scanf("%d", col + i);
    for(int i = 1; i <= n; ++i){
        rndval[i] = rnd();
        while(!rndval[i]) rndval[i] = rnd();
    }
    int ans1 = 0, ans2 = 1;
    unordered_map<LL, int> pos;
    int last = 0;
    LL v = 0; pos[0] = 0;
    for(int i = 1; i <= 2 * n; ++i){
        v ^= rndval[col[i]];
        if(pos.count(v)){
            int pre = pos[v];
            if(pre == last){
                ++ans1;
                ans2 = 1ll * ans2 * check(pre + 1, i) % ha;
                last = i;
            } else rht[pre + 1] = i;
        }
        pos[v] = i;
    }
    printf("%d %d\n", ans1, ans2);
    memset(rht, 0, sizeof(int) * (2 * n + 1));
}

int main(){
    int T; scanf("%d", &T);
    while(T--) work();
    return 0;
}

/*
思路：
1. 将每种颜色用一个非 0 随机值代替
2. 如果有一个区间异或和为 0，那它内部每种颜色恰好出现两次。
   如果它不被其它异或和为 0 的区间包含，
   那么这个区间就是独立的，必须在这个区间中选一个数进行染色
3. 对于一个独立区间，并不是内部任取一个数染色均可，必须保证把选的
   数染色之后，整个独立区间都能被染色
4. 假设 [L,R] 是独立区间，其内部有一个区间 [l,r] 的异或和也为 0，
   那么不能选 [l,r] 里面的颜色。除了这样的内部异或和为 0 的区间外，
   [L,R] 中的其它位置选了之后都能让整个区间被染色。
*/