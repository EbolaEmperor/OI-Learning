#include <bits/stdc++.h>
using namespace std;

const int N = 330;
const int M = 100005;

template <typename fl,typename co> 
class MincostMaxflow
{
private:
    struct Edge{
        int from, to, next;
        fl flow;
        co cost;
    } e[M];
    int s, t, h[N], p[N], sum;
    fl a[N];
    co d[N];
    bool inq[N];

    bool BellmanFord(fl& flow, co& cost){
        for(int i = 0; i < N; i++)
            d[i] = numeric_limits<co>::max();
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        a[s] = numeric_limits<fl>::max();
        inq[s]=1;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int o = q.front();
            for(int i = h[o]; ~i; i = e[i].next)
                if(e[i].flow > 0 && d[o] + e[i].cost < d[e[i].to]){
                    d[e[i].to] = d[o] + e[i].cost;
                    a[e[i].to] = min(a[o], e[i].flow);
                    p[e[i].to] = i;
                    if(!inq[e[i].to]){
                        inq[e[i].to] = 1;
                        q.push(e[i].to);
                    }
                }
            q.pop(); inq[o] = 0;
        }
        if(d[t] == numeric_limits<co>::max()) return 0;
        flow += a[t];
        cost += d[t] * (co) a[t];
        for(int i = t; i != s; i = e[p[i]].from){
            e[p[i]].flow -= a[t];
            e[p[i] ^ 1].flow += a[t];
        }
        return 1;
    }
    
public:
    void add_edge(int u,int v,fl w,co f){
        e[++sum] = (Edge){u, v, h[u], w, f}; h[u] = sum;
        e[++sum] = (Edge){v, u, h[v], 0, -f}; h[v] = sum;
    }
    pair<fl,co> MCMF(){
        fl flow = 0;
        co cost = 0;
        while(BellmanFord(flow, cost));
        return make_pair(flow, cost);
    }
    void init(int x,int y){
        s = x;
        t = y;
        sum = -1;
        memset(h, -1, sizeof(h));
    }
};
MincostMaxflow<int, long long> mcmf;

// [xl[i], xr[i]]: 把偷的珠宝按 x 坐标排序后，第 i 个珠宝的可行取值范围
// yl, yr 同理
int xl[N], xr[N], yl[N], yr[N];
int n, x[N], y[N];
long long v[N];
int m, a[N], b[N];
char typ[N];

long long stole(int k){
    int s = 0, t = 2 * (k + n) + 1;
    mcmf.init(s, t);
    for(int i = 1; i <= k; i++){
        mcmf.add_edge(s, i, 1, 0);
        mcmf.add_edge(i + k, t, 1, 0);
        xl[i] = yl[i] = 0;
        xr[i] = yr[i] = 200;
    }
    for(int i = 1; i <= n; i++)
        mcmf.add_edge(2 * k + i, 2 * k + n + i, 1, -v[i]);
    for(int i = 1; i <= m; i++){
        if(typ[i] == 'L') // 按 x 坐标排序后，第 (b[i]+1)...k 个必须 > a[i]
            for(int j = b[i] + 1; j <= k; j++)
                xl[j] = max(xl[j], a[i] + 1);
        if(typ[i] == 'R') // 按 x 坐标排序后，第 1...(k-b[i]) 个必须 < a[i]
            for(int j = 1; j <= k - b[i]; j++)
                xr[j] = min(xr[j], a[i] - 1);
        if(typ[i] == 'D') // 按 y 坐标排序后，第 (b[i]+1)...k 个必须 > a[i]
            for(int j = b[i] + 1; j <= k; j++)
                yl[j] = max(yl[j], a[i] + 1);
        if(typ[i] == 'U') // 按 y 坐标排序后，第 1...(k-b[i]) 个必须 < a[i]
            for(int j = 1; j <= k - b[i]; j++)
                yr[j] = min(yr[j], a[i] - 1);
    }
    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= n; j++){
            if(x[j] >= xl[i] && x[j] <= xr[i])
                mcmf.add_edge(i, 2 * k + j, 1, 0);
            if(y[j] >= yl[i] && y[j] <= yr[i])
                mcmf.add_edge(2 * k + n + j, i + k, 1, 0);
        }
    return -mcmf.MCMF().second;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> x[i] >> y[i] >> v[i];
    cin >> m;
    for(int i = 1; i <= m; i++)
        cin >> typ[i] >> a[i] >> b[i];
    
    long long ans = 0;
    for(int k = 1; k <= n; k++)
        ans = max(ans, stole(k));
    cout << ans << endl;
    return 0;
}