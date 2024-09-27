#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int M = 3e5, N = M + 5;
int n;
vector<int> L[N], R[N];
int pw2[N], pw3[N];

int main(){
    scanf("%d", &n);
    int l1, r1;
    for(int i = 1; i <= n; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        if(i == 1) l1 = l, r1 = r;
        else{
            L[l].push_back(i);
            R[r + 1].push_back(i);
        }
    }
    pw2[0] = pw3[0] = 1;
    for(int i = 1; i <= n; i++) pw2[i] = 2 * pw2[i - 1] % ha;
    for(int i = 1; i <= n; i++) pw3[i] = 3ll * pw3[i - 1] % ha;
    int ans = 0;
    set<int> ones;
    for(int k = 0; k <= M; k++){
        for(int i : L[k]) ones.insert(i);
        for(int i : R[k]) ones.erase(i);
        if(ones.empty()){
            ans = (ans + (k >= l1 && k <= r1) * pw2[n - 1]) % ha;
        } else {
            int i = *(--ones.end());
            ans = (ans + 1ll * pw3[i - 2] * pw2[n - i + 1]) % ha;
        }
    }
    cout << ans << endl;
    return 0;
}