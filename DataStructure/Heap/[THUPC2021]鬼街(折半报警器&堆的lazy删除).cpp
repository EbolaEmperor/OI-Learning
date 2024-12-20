#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100010;
vector<int> factor[N];
int n, m, cnt[N];
int nMnt = 0, start[N], thrshd[N], val[N];
priority_queue<pair<int,int>> alrm[N];
unordered_map<int, int> alrmThr[N];
vector<int> ans;

void init(){
    static bool mark[N];
    static int prm[N], tot = 0;
    for(int i = 2; i < N; i++){
        if(!mark[i]){
            prm[++tot] = i;
            factor[i].push_back(i);
        }
        for(int j = 1; j <= tot && i * prm[j] < N; j++){
            mark[i * prm[j]] = 1;
            factor[i * prm[j]] = factor[i];
            if(i % prm[j]) factor[i * prm[j]].push_back(prm[j]);
            else break;
        }
    }
}

void setalrm(int id, int almThr){
    for(int p : factor[val[id]]){
        start[id] += cnt[p];
        alrm[p].push(make_pair(-(cnt[p] + almThr), id));
        alrmThr[id][p] = cnt[p] + almThr;
    }
}

void alrming(int id){
    int sum = 0, k = factor[val[id]].size();
    for(int p : factor[val[id]])
        sum += cnt[p];
    if(sum - start[id] >= thrshd[id]){
        alrmThr[id].clear();
        return ans.push_back(id);
    }
    thrshd[id] -= sum - start[id];
    start[id] = 0;
    setalrm(id, (thrshd[id] - 1) / k + 1);
}

void addGhost(int x, int y){
    for(int p : factor[x]){
        cnt[p] += y;
        while(!alrm[p].empty()){
            auto [thr, id] = alrm[p].top();
            if(alrmThr[id].empty() || -thr != alrmThr[id][p]){
                alrm[p].pop();
                continue;
            }
            if(cnt[p] < -thr) break;
            alrming(id);
        }
    }
}

void addMonitor(int x, int y){
    thrshd[++nMnt] = y;
    val[nMnt] = x;
    if(y == 0) return ans.push_back(nMnt);
    setalrm(nMnt, (y - 1) / factor[x].size() + 1);
}

signed main(){
    init();
    scanf("%lld%lld", &n, &m);
    int lastans = 0;
    while(m--){
        int op, x, y;
        scanf("%lld%lld%lld", &op, &x, &y);
        y ^= lastans;
        if(op == 0){
            addGhost(x, y);
            sort(ans.begin(), ans.end());
            printf("%lld", (int)ans.size());
            for(int x : ans) printf(" %lld", x);
            printf("\n");
            lastans = ans.size();
            ans.clear();
        }
        else addMonitor(x, y);
    }
    return 0;
}