#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
int n, q, l[N], r[N];
int jump[N][20];

void initJump(){
    set<int> knots;
    unordered_set<int> rights;
    int p = 1;
    knots.insert(INT_MAX);
    // knots: 目前已经加入的所有区间端点
    // rights: 目前已经加入的所有区间右端点，用于判断每个端点是左端点还是右端点
    // 注意当 l=r 时需要特判
    for(int i = 1; i <= n; i++){
        if(i > 1){
            knots.erase(l[i - 1]);
            if(l[i - 1] != r[i - 1]){
                knots.erase(r[i - 1]);
                rights.erase(r[i - 1]);
            }
        }
        while(p <= n){
            auto it = knots.upper_bound(r[p]), jt = it;
            // 要想在已选择的区间里再加一个无交的区间 [l,r]，
            // 那么 r 右边第一个已选择端点必须是左端点，且该端点的前一个端点必须 <l
            if(rights.find(*it) == rights.end() && 
               (it == knots.begin() || *(--jt) < l[p])){
                if(l[p] != r[p]) knots.insert(r[p]), rights.insert(r[p]);
                knots.insert(l[p]); p++;
            }
            else break;
        }
        jump[i][0] = p;
    }
    jump[n + 1][0] = n + 1;
    for(int k = 1; k <= 17; k++)
        for(int i = 1; i <= n + 1; i++)
            jump[i][k] = jump[jump[i][k - 1]][k - 1];
}

int query(){
    int L, R, ans = 0;
    cin >> L >> R;
    for(int i = 17; i >= 0; i--)
        if(jump[L][i] <= R){
            L = jump[L][i];
            ans += (1 << i);
        }
    if(L <= R) ans++;
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", l + i, r + i);
    initJump();
    scanf("%d", &q);
    while(q--) cout << query() << "\n";
    return 0;
}