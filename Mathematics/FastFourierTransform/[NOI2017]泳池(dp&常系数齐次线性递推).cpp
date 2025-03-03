#include "Polynomial.h"
// 提交时需要手动把头文件里的 Poly_logM 改成 15

Polynomial getR(int n, const Polynomial &p){
    Polynomial H(p.degree() - 1), R(0);
    H[1] = 1;
    R[0] = 1;
    for(; n; n >>= 1){
        if(n & 1) R = R * H % p;
        H = H * H % p;
    }
    return R;
}

int computeRecur(int n, const vector<int> &coef, const vector<int> &initVal){
    int k = coef.size();
    Polynomial p(k);
    for(int i = 1; i <= k; i++){
        p[k - i] = (Mod - coef[i - 1]) % Mod;
    }
    p[k] = 1;
    auto R = getR(n, p);
    int ans = 0;
    for(int i = 0; i < k; i++)
        ans = (ans + 1ll * initVal[i] * R[i]) % Mod;
    return ans;
}
// 以上是常系数齐次线性递推板子

const int K = 1005;
int h[K][K], n, p, nop;

int getAns(int k){
    memset(h, 0, sizeof(h));
    for(int i = 0; i <= k + 1; i++) h[i][0] = 1;
    for(int i = k; i > 0; i--){
        for(int j = 1; i * j <= k; j++){
            int tmp = 1;
            for(int k = 1; k <= j; k++){
                tmp = 1ll * tmp * p % Mod;
                h[i][j] = (h[i][j] + 1ll * nop * tmp % Mod 
                                   * h[i + 1][k - 1] % Mod * h[i][j - k]) % Mod;
            }
            h[i][j] = (h[i][j] + 1ll * h[i + 1][j] * tmp) % Mod;
        }
    }
    vector<int> coef(k + 1);
    for(int i = 0; i <= k; i++)
        coef[i] = 1ll * h[1][i] * nop % Mod;
    vector<int> initVal(k + 1, 0);
    initVal[k] = 1;
    return 1ll * computeRecur(n + k + 1, coef, initVal) 
               * Pow(nop, Mod - 2) % Mod;
}

int main(){
    int x, y, k;
    cin >> n >> k >> x >> y;
    p = 1ll * x * Pow(y, Mod - 2) % Mod;
    nop = (Mod + 1 - p) % Mod;
    int ans = (getAns(k) - getAns(k - 1) + Mod) % Mod;
    cout << ans << endl;
    return 0;
}