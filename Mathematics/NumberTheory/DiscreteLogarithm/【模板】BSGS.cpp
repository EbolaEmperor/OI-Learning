#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

// 对于单次求解，取 sq = sqrt(ha)，即可做到 O(sq) 预处理、O(sq) 询问。
// 对于模数、底数不变的多组询问，取 sq = sqrt(ha * q) 是最优的。
// 但仍然不够优。如果模数和底数都不变，可以使用隔壁的 BSGS-Faster 算法。
class BSGS{
private:
    int ha, a, sq, base;
    unordered_map<int, int> save;
    void ExGcd(LL a, LL b, LL &x, LL &y) const{
        if(b == 0){x = 1; y = 0; return;}
        ExGcd(b, a % b, x, y);
        LL t = x; x = y;
        y = t - (a / b) * y;
    }
public:
    BSGS(int p, int a, int _sq = -1): ha(p), a(a){
        sq = (_sq == -1) ? ceil(sqrt(ha)) : _sq;
        base = 1;
        for(int i = 0; i < sq; i++){
            if(!save.count(base)) save[base] = i;
            base = (LL) base * a % ha;
        }
    }

    int log(int b) const{
        LL now = 1, d, y;
        for(LL i = 0; i * sq < ha; i++){
            ExGcd(now, ha, d, y);
            d = (d % ha + ha) % ha;
            d = d * b % ha;
            auto it = save.find(d);
            if(it != save.end()) return i * sq + it->second;
            now = base * now % ha;
        }
        return -1;
    }
};

int main(){
    int p, g, q, y;
    scanf("%d%d%d", &p, &g, &q);
    BSGS bsgs(p, g, ceil(sqrt((LL) p * q)));
    while(q--){
        scanf("%d", &y);
        printf("%d\n", bsgs.log(y));
    }
    return 0;
}
