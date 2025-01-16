#include <iostream>
#include <vector>
#include <map>
#define int long long
using namespace std;

const int MAXN = 1e5 + 5;
int m;
int n[MAXN], l[MAXN], r[MAXN], tot[MAXN];
vector<int> a[MAXN], c[MAXN];
map<int, vector<int>> mp;
// mp[x]: 是一个 vector，表示有哪些集合包含 x 这个数
map<int, int> cnt[MAXN];

int L, R, N;

int work(){
    cin >> m;
    N = L = R = 0;
    mp.clear();
    for(int i = 1; i <= m; i++){
        cin >> n[i] >> l[i] >> r[i];
        N += n[i];
        L += l[i];
        R += r[i];
        a[i].clear();
        c[i].clear();
        cnt[i].clear();
        for(int j = 0; j < n[i]; j++){
            int x;
            cin >> x;
            a[i].push_back(x);
            mp[x].push_back(i);
        }
        tot[i] = 0;
        for(int j = 0; j < n[i]; j++){
            int x;
            cin >> x;
            c[i].push_back(x);
            tot[i] += c[i][j];
            cnt[i][a[i][j]] = c[i][j];
        }
    }
    if(R - L + 1 > N) return 0;
    int ans = 1e18;
    for(int len = L; len <= R; len++){
        if(!mp.count(len)) return 0;
        int cntlen = 0, s = R;
        for(int i : mp[len]){
            int tmp = tot[i] - cnt[i][len];
            if(tmp < l[i]) cntlen += l[i] - tmp, s += l[i];
            else if(tmp > r[i]) s += r[i];
            else s += tmp;
            s -= r[i];
        }
        if(s < len) cntlen += len - s;
        ans = min(ans, cntlen);
    }
    return ans;
}

signed main(){
    int t;
    cin >> t;
    while(t--) cout << work() << "\n";
    return 0;
}