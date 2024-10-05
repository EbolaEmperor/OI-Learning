#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int N = 1e6 + 5, M = 1e7 + 5;
int trmin[M << 2], tlen;
vector<int> prifac[N];
int stpos[N];
set<int> openpos[N];
bool status[N];

void init(int n){
    static bool mark[N];
    static int prm[N], tot = 0;
    prifac[1].push_back(1);
    for(int i = 2; i <= n; i++){
        if(!mark[i]){
            prm[++tot] = i;
            prifac[i].push_back(i);
        }
        for(int j = 1; j <= tot && i * prm[j] <= n; j++){
            mark[i * prm[j]] = 1;
            prifac[i * prm[j]] = prifac[i];
            if(i % prm[j] == 0) break;
            else prifac[i * prm[j]].push_back(prm[j]);
        }
    }
}

void update(int o, int l, int r, int k, int x){
    if(l == r){
        trmin[o] = x;
        return;
    }
    int mid = (l + r) / 2;
    if(k <= mid) update(o << 1, l, mid, k, x);
    else update(o << 1 | 1, mid + 1, r, k, x);
    trmin[o] = min(trmin[o << 1], trmin[o << 1 | 1]);
}

int qmin(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return trmin[o];
    int mid = (l + r) / 2, ans = inf;
    if(nl <= mid) ans = min(ans, qmin(o << 1, l, mid, nl, nr));
    if(nr > mid) ans = min(ans, qmin(o << 1 | 1, mid + 1, r, nl, nr));
    return ans;
}

void setup(int pos, int val){
    if(!openpos[val].empty()){
        auto it = openpos[val].lower_bound(pos);
        if(it != openpos[val].end())
            update(1, 1, tlen, pos, *it);
        if(it != openpos[val].begin()){
            --it;
            update(1, 1, tlen, *it, pos);
        }
    }
    openpos[val].insert(pos);
}

void setdown(int pos, int val){
    auto it = openpos[val].find(pos);
    update(1, 1, tlen, pos, inf);
    if(it != openpos[val].begin()){
        auto jt = it; --jt; ++it;
        update(1, 1, tlen, *jt, it == openpos[val].end() ? inf : *it);
    }
    openpos[val].erase(pos);
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    init(n);
    stpos[1] = 1;
    for(int i = 2; i <= n + 1; i++)
        stpos[i] = stpos[i - 1] + prifac[i - 1].size();
    tlen = stpos[n + 1] - 1;
    memset(trmin, 0x3f, sizeof(trmin));

    int x, y; char order[5];
    while(q--){
        scanf("%s%d", order, &x);
        if(order[0] == 'S'){
            for(int i = 0; i < prifac[x].size(); i++)
                status[x] == 0 ?
                setup(stpos[x] + i, prifac[x][i]) :
                setdown(stpos[x] + i, prifac[x][i]);
            status[x] ^= 1;
        } else {
            scanf("%d", &y);
            puts(qmin(1, 1, tlen, stpos[x], stpos[y + 1] - 1) < stpos[y + 1] ? "DA" : "NE");
        }
    }
    return 0;
}