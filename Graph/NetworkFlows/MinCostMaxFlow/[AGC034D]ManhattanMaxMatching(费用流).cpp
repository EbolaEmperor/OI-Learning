#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
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

int main(){
    int n;
    scanf("%d", &n);
    mcmf.init(0, 2 * n + 5);
    for(int i = 1; i <= n; i++){
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        mcmf.add_edge(0, i, c, 0);
        mcmf.add_edge(i, 2 * n + 1, c, x + y);
        mcmf.add_edge(i, 2 * n + 2, c, x - y);
        mcmf.add_edge(i, 2 * n + 3, c, -x + y);
        mcmf.add_edge(i, 2 * n + 4, c, -x - y);
    }
    for(int i = 1; i <= n; i++){
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        mcmf.add_edge(i + n, 2 * n + 5, c, 0);
        mcmf.add_edge(2 * n + 1, i + n, c, -x - y);
        mcmf.add_edge(2 * n + 2, i + n, c, -x + y);
        mcmf.add_edge(2 * n + 3, i + n, c, x - y);
        mcmf.add_edge(2 * n + 4, i + n, c, x + y);
    }
    cout << -mcmf.MCMF().second << endl;
    return 0;
}