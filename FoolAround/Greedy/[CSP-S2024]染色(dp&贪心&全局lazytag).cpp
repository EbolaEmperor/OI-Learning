#include <iostream>
#include <cstring>
using namespace std;

const int N = 200010;
int lastpos[N * 5], pre[N], a[N], n;
long long f[N];
// f[i][j]: 前 i 个数，最后一段同色区间为 [j,i] 时的最大得分
//          因为 f[i][...] 只和 f[i-1][...] 有关，所以把第一维压缩掉

long long work(){
    memset(pre, 0, sizeof(pre));
    memset(lastpos, 0, sizeof(lastpos));
    memset(f, 0, sizeof(f));
    long long globalAdd = 0, globalMax = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(lastpos[a[i]]) pre[i] = lastpos[a[i]];
        lastpos[a[i]] = i;
    }
    for(int i = 1; i <= n; i++){
        f[i] = globalMax;
        if(pre[i] && pre[i] < i-1)
            f[i] = max(f[i], f[pre[i] + 1] + globalAdd + a[i]);
        int tmpAdd = (a[i] == a[i-1]) ? a[i] : 0;
        globalMax = max(globalMax + tmpAdd, f[i]);
        globalAdd += tmpAdd;
        f[i] -= globalAdd;
    }
    return globalMax;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T; cin >> T;
    while(T--) cout << work() << endl;
    return 0;
}