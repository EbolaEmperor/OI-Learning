#include <bits/stdc++.h>
#define LL long long
using namespace std;

map<pair<LL,LL>, LL> rec;
LL zebra[30];

LL dp(LL i, LL p){
    if(i < 0) exit(0);
    if (i == 0) return (p == 0);
    if (p == 0) return 1;
    if (p == 1) {
        int idx = upper_bound(zebra, zebra + 30, i) - zebra - 1;
        return idx + 1;
    }
    if (rec.count({i, p})) return rec[{i, p}];
    auto it = upper_bound(zebra, zebra + 30, i);
    LL z = *(--it);
    return rec[{i, p}] = dp(z - 1, p) + dp(i - z, p - 1);
}

int main(){
    zebra[0] = 1;
    for (LL i = 1; i < 30; i++){
        zebra[i] = zebra[i - 1] * 4 + 1;
    }
    LL t, l, r, k;
    cin >> t;
    while (t--){
        cin >> l >> r >> k;
        cout << dp(r, k) - dp(l - 1, k) << "\n";
    }
    return 0;
}