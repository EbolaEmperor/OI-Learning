#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int N = 200010;
int n, q, l[N], r[N];
int jump[N][20];
bool isRight[N << 1];

void initJump(){
    set<int> knots;
    int p = 1;
    knots.insert(2 * n + 1);
    for(int i = 1; i <= n; i++){
        if(i > 1){
            knots.erase(l[i - 1]);
            if(l[i - 1] != r[i - 1]) knots.erase(r[i - 1]);
        }
        while(p <= n){
            auto it = knots.upper_bound(r[p]), jt = it;
            if(!isRight[*it] && (it == knots.begin() || *(--jt) < l[p])){
                if(l[p] != r[p]) knots.insert(r[p]), isRight[r[p]] = 1;
                knots.insert(l[p]), isRight[l[p]] = 0;
                p++;
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

void discre(){
    static int vals[N << 1];
    for(int i = 1; i <= n; i++){
        vals[i * 2 - 1] = l[i];
        vals[i * 2] = r[i];
    }
    sort(vals + 1, vals + 1 + 2 * n);
    int m = unique(vals + 1, vals + 1 + 2 * n) - (vals + 1);
    for(int i = 1; i <= n; i++){
        l[i] = lower_bound(vals + 1, vals + 1 + m, l[i]) - vals;
        r[i] = lower_bound(vals + 1, vals + 1 + m, r[i]) - vals;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> l[i] >> r[i];
    discre();
    initJump();
    cin >> q;
    while(q--) cout << query() << "\n";
    return 0;
}