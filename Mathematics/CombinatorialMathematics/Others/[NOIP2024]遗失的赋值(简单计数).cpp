#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100010;
const int ha = 1e9 + 7;
pair<int,int> sop[N];
int n, m, v;

int Pow(int a, long long b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int work(){
    cin >> n >> m >> v;
    for(int i = 1; i <= m; i++)
        cin >> sop[i].first >> sop[i].second;
    sort(sop + 1, sop + 1 + m);
    for(int i = 2; i <= m; i++){
        if(sop[i].first == sop[i-1].first && sop[i].second != sop[i-1].second)
            return 0;
    }
    m = unique(sop + 1, sop + 1 + m) - sop - 1;
    int ans = Pow(v, 2ll * (sop[1].first - 1) + 2ll * (n - sop[m].first));
    for(int i = 1; i < m; i++){
        ans = 1ll * ans * (Pow(v, 2ll * (sop[i+1].first - sop[i].first))
                         - 1ll * Pow(v, sop[i+1].first - sop[i].first - 1) * (v-1) % ha + ha) % ha;
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    while(T--) cout << work() << endl;
    return 0;
}