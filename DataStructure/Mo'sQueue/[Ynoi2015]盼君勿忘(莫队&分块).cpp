#include <bits/stdc++.h>
using namespace std;

const int N = 100010, S = 320;
int n, m, a[N], ans[N];
int pow2baby[S+5], pow2giant[S+5];
// more: The numbers occurs more than S times in the whole sequence
vector<int> more;
// ismore[c]: whether c is in "more"
bool ismore[N];
// occur[i]:  The occur times of number i in current range [l,r]
int occ[N];
// sum[c]: The sum of numbers who occurs c times in current range [l,r]
int sum[S+5];

struct Query{
    int l, r, p, id;
    bool operator < (const Query &rhs) const{
        return l / S == rhs.l / S ? r < rhs.r : l < rhs.l;
    }
} q[N];

int pow2(int n, int p){
    return 1ll * pow2giant[n / S] * pow2baby[n % S] % p;
}

void ins(int c){
    if(!ismore[c]) sum[occ[c]] -= c, sum[++occ[c]] += c;
    else ++occ[c];
}

void del(int c){
    if(!ismore[c]) sum[occ[c]] -= c, sum[--occ[c]] += c;
    else --occ[c];
}

void doQuery(int len, int id, int p){
    pow2baby[0] = pow2giant[0] = 1;
    for(int i = 1; i < S; ++i)
        pow2baby[i] = 2 * pow2baby[i-1] % p;
    pow2giant[1] = 2 * pow2baby[S-1] % p;
    for(int i = 2; i <= S; ++i)
        pow2giant[i] = 1ll * pow2giant[i-1] * pow2giant[1] % p;
    int all = pow2(len, p);
    // The contribution of a number c occurs k times is c * (2^len - 2^(len-k)),
    // which means the all subsequences minus the subsequences where c does not occur.
    // For k <= S, sum up all such c that occurs k times.
    // For k > S, the number of such k will not ecceed S, just list all such k. 
    for(int k = 0; k <= S; ++k)
        ans[id] = (ans[id] + (1ll * all - pow2(len - k, p) + p) * sum[k]) % p;
    for(int c : more)
        ans[id] = (ans[id] + (1ll * all - pow2(len - occ[c], p) + p) * c) % p;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%d", a + i), ++occ[a[i]];
    for(int i = 1; i <= n; ++i)
        if(occ[i] > S) more.push_back(i), ismore[i] = true;
    memset(occ, 0, sizeof(occ));
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].p), q[i].id = i;
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i){
        while(l < q[i].l) del(a[l++]);
        while(l > q[i].l) ins(a[--l]);
        while(r < q[i].r) ins(a[++r]);
        while(r > q[i].r) del(a[r--]);
        doQuery(q[i].r - q[i].l + 1, q[i].id, q[i].p);
    }
    for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}