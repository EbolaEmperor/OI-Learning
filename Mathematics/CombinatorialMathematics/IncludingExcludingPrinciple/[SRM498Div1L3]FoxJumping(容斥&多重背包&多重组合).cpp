#include <bits/stdc++.h>
using namespace std;

const int ha = 10007;
const int N = 1605;
int C[N][N], fact[N], ifact[N];
int n[2], hn[2], R;
vector<int> B;

inline void add(int &x, int y){
    x = (x + y >= ha) ? (x + y - ha) : x + y;
}
inline void mns(int &x, int y){
    x = (x - y < 0) ? (x - y + ha) : x - y;
}
int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = a * a % ha)
        if(b & 1) ans = ans * a % ha;
    return ans;
}

void init(){
    fact[0] = 1;
    for(int i = 0; i < N; i++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % ha;
        if(i) fact[i] = fact[i - 1] * i % ha;
    }
    ifact[N - 1] = Pow(fact[N - 1], ha - 2);
    for(int i = N - 1; i >= 1; i--)
        ifact[i - 1] = ifact[i] * i % ha;
}

void work(){
    static int f[2][N][N], sf[2][N][N];
    for(int dim = 0; dim < 2; dim++){
        f[dim][0][0] = 1;
        for(int t = 0; t < R; t++){
            sf[dim][t][0] = f[dim][t][0];
            for(int i = 1; i <= n[dim]; i++)
                sf[dim][t][i] = (sf[dim][t][i - 1] + f[dim][t][i]) % ha;
            for(int i = 0; i <= n[dim]; i++){
                f[dim][t + 1][i] = sf[dim][t][i];
                if(i > hn[dim]) mns(f[dim][t + 1][i], sf[dim][t][i - hn[dim] - 1]);
            }
        }
    }
    for(int& x : B) x /= 10;
    // g[i][j]: 考虑在 B 里用 i 个数字构成 10j 的方案，这些方案的 (c[1]!...c[B]!)^{-1} 之和
    //          其中 c[k] 表示 B 里的第 k 个数字选了几个
    //          至于为什么这么定义，是因为容斥里钦定非法步长的时候，会出现多重组合
    static int g[N / 10][N / 10];
    g[0][0] = 1;
    for(int x : B){
        for(int i = 80; i >= 1; i--)
            for(int k = 1; k <= i; k++)
                for(int j = k * x; j <= 80; j++)
                    add(g[i][j], ifact[k] * g[i - k][j - k * x] % ha);
    }
    int totans = 0;
    // 外层容斥：钦定走了 i 步非法步长，这些非法步长之和为 j，剩下的不管
    for(int i = 0; i <= 80; i++)
        for(int j = 0; j <= 80; j++){
            if(!g[i][j]) continue;
            int cn[2];
            cn[0] = n[0] - j * 10;
            cn[1] = n[1] - j * 10;
            if(cn[0] < 0 || cn[1] < 0) continue;
            int ans = 0, cR = R - i;
            if(!cn[0] && !cn[1]) ans = (cR == 0);
            else {
                // 内层容斥：钦定停 i 步，剩下的不管
                for(int i = 1; i <= cR; i++){
                    int tmp = 1ll * C[cR][i - 1] 
                                * f[0][cR - i + 1][cn[0]] 
                                * f[1][cR - i + 1][cn[1]] % ha;
                    if(i & 1) add(ans, tmp);
                    else mns(ans, tmp);
                }
            }
            ans = 1ll * C[R][i] * fact[i] * g[i][j] * ans % ha;
            if(i & 1) mns(totans, ans);
            else add(totans, ans);
        }
    cout << totans << endl;
}

int main(){
    init();
    int sz;
    cin >> n[0] >> n[1] >> hn[0] >> hn[1] >> R >> sz;
    B.resize(sz);
    for (int i = 0; i < sz; i++)
        cin >> B[i];
    sort(B.begin(), B.end());
    work();
    return 0;
}


//---------------------------- Subtasks -------------------------------

void subtask_Bis0(){
    static int f[2][N];
    int jump[2][N] = {0};
    
    for(int dim = 0; dim < 2; dim++){
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int t = 1, cc = 0; t <= R; t++, cc ^= 1){
            for(int i = 1; i <= n[dim]; i++)
                add(f[cc][i], f[cc][i - 1]);
            for(int i = 0; i <= n[dim]; i++){
                f[cc ^ 1][i] = f[cc][i];
                if(i > hn[dim]) mns(f[cc ^ 1][i], f[cc][i - hn[dim] - 1]);
            }
            jump[dim][t] = f[cc ^ 1][n[dim]];
        }
    }
    int ans = 0;
    for(int i = 1; i <= R; i++){
        int tmp = 1ll * C[R][i - 1] * jump[0][R - i + 1] * jump[1][R - i + 1] % ha;
        if(i & 1) add(ans, tmp);
        else mns(ans, tmp);
    }
    cout << ans << endl;
}

void subtask_Bis1(){
    static int f[2][N][N], sf[2][N][N];
    for(int dim = 0; dim < 2; dim++){
        f[dim][0][0] = 1;
        for(int t = 0; t < R; t++){
            sf[dim][t][0] = f[dim][t][0];
            for(int i = 1; i <= n[dim]; i++)
                sf[dim][t][i] = (sf[dim][t][i - 1] + f[dim][t][i]) % ha;
            for(int i = 0; i <= n[dim]; i++){
                f[dim][t + 1][i] = sf[dim][t][i];
                if(i > hn[dim]) mns(f[dim][t + 1][i], sf[dim][t][i - hn[dim] - 1]);
            }
        }
    }
    int totans = 0;
    for(int b = 0; b <= R; b++){
        int cn[2];
        cn[0] = n[0] - b * B[0];
        cn[1] = n[1] - b * B[0];
        if(cn[0] < 0 || cn[1] < 0) break;
        int ans = 0, cR = R - b;
        if(!cn[0] && !cn[1]) ans = (cR == 0);
        else {
            for(int i = 1; i <= cR; i++){
                int tmp = 1ll * C[cR][i - 1] 
                            * f[0][cR - i + 1][cn[0]] 
                            * f[1][cR - i + 1][cn[1]] % ha;
                if(i & 1) add(ans, tmp);
                else mns(ans, tmp);
            }
        }
        ans = C[R][b] * ans % ha;
        if(b & 1) mns(totans, ans);
        else add(totans, ans);
    }
    cout << totans << endl;
}