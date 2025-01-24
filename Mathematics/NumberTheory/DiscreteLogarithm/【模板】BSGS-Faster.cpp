#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

class BSGS{
protected:
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
            // if(i % 100  == 0) cout << i << endl;
        }
    }
    int log(int b) const{
        int now = 1; LL d, y;
        for(int i = 0; i * sq < ha; i++){
            ExGcd(now, ha, d, y);
            d = (d % ha + ha) % ha;
            d = (LL) d * b % ha;
            auto it = save.find(d);
            if(it != save.end()) return i * sq + it->second;
            now = (LL) base * now % ha;
        }
        return -1;
    }
};

// 预处理 O( P^0.75 / sqrt(log P) )
// 单次询问 O(log P)
class BSGSFaster : public BSGS{
private:
    vector<int> H, prime, vis;
    int H0, h;
    void init(){
        h = ceil(sqrt(ha)) + 1;
        H0 = BSGS::log(ha - 1);
        H.resize(h + 1, 0);
        vis.resize(h + 1, 0);
        for(int i = 2; i <= h; i++){
            if(!vis[i]){
                prime.push_back(i);
                H[i] = BSGS::log(i);
            }
            for(int p : prime){
                if(i * p > h) break;
                H[i * p] = (H[i] + H[p]) % (ha - 1);
                vis[i * p] = 1;
                if(i % p == 0) break;
            }
        }
    }
public:
    BSGSFaster(int P, int g)
      : BSGS(P, g, ceil(sqrt((LL) P * sqrt(P) / std::log(P)))) {
        init();
    }
    int log(int b) const{
        if(b <= h) return H[b];
        int d = ha / b, r = ha % b;
        return (r < b - r) ?
               ((H0 + log(r)) % (ha - 1) - H[d] + ha - 1) % (ha - 1) :
               (log(b - r) - H[d + 1] + ha - 1) % (ha - 1);;
    }
};

int main()
{
    int p, g, q, y;
    scanf("%d%d%d", &p, &g, &q);
    BSGSFaster bsgs(p, g);
    while(q--){
        scanf("%d", &y);
        printf("%d\n", bsgs.log(y));
    }
    return 0;
}
