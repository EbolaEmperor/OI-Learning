#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 100010;
int n, m[3], sg[3][N], max_sg[3], coef[3][600];
vector<int> G[3][N];

void add(int &x, int y){
    x += y;
    if (x >= ha) x -= ha;
}

int Pow(int a, int b){
    int res = 1;
    while (b){
        if (b & 1) res = 1ll * res * a % ha;
        a = 1ll * a * a % ha;
        b >>= 1;
    }
    return res;
}

const int K = Pow(10, 18);
int pwK[N];

void compute_SG(int gid){
    memset(sg[gid], 0, sizeof(sg[gid]));
    static bool mex[N];
    memset(mex, false, sizeof(mex));
    auto update_mex = [&](int i, int c){
        for (auto v : G[gid][i])
            if (v > i) mex[sg[gid][v]] = c;
    };
    for (int i = n; i >= 1; i--){
        update_mex(i, true);
        while (mex[sg[gid][i]]) sg[gid][i]++;
        max_sg[gid] = max(max_sg[gid], sg[gid][i]);
        add(coef[gid][sg[gid][i]], pwK[i]);
        update_mex(i, false);
    }
}

int main(){
    cin >> n;
    pwK[0] = 1;
    for (int i = 1; i < N; i++)
        pwK[i] = 1ll * pwK[i - 1] * K % ha;
    for (int i = 0; i < 3; i++){
        cin >> m[i];
        for (int j = 0; j < m[i]; j++){
            int x, y;
            cin >> x >> y;
            if(y < x) swap(x, y);
            G[i][x].push_back(y);
        }
    }
    for (int i = 0; i < 3; i++)
        compute_SG(i);
    int ans = 0;
    for (int sg1 = 0; sg1 <= max_sg[0]; sg1++)
        for (int sg2 = 0; sg2 <= max_sg[1]; sg2++)
            ans = (ans + 1ll * coef[0][sg1] * coef[1][sg2] % ha * coef[2][sg1 ^ sg2]) % ha;
    cout << ans << endl;
    return 0;
}