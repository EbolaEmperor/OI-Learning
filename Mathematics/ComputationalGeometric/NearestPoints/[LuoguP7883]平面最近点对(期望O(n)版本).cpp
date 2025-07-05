#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400010;
const int MOD = 10000019;

struct Point{int x, y;};

long long grid_index(const Point &p, const int &N, const double &h){
    return (long long) floor(p.x / h) * N + floor(p.y / h);
}

long long dist2(const Point &p1, const Point &p2){
    return (long long) (p1.x-p2.x) * (p1.x-p2.x) + (long long) (p1.y-p2.y) * (p1.y-p2.y) ;
}

long long nearest_dist(const Point p[], const int &n){
    static int hash[MOD][10], hash_idx[MOD];
    memset(hash_idx, 0, sizeof(hash_idx));
    
    long long h2 = dist2(p[0], p[1]);
    if(h2 == 0) return 0;
    double h = sqrt(h2);
    int N = ceil(2e7 / h);

    auto add_point = [&](const int &i){
        int g = grid_index(p[i], N, h) % MOD;
        if(hash_idx[g] == 10) exit(-1);
        hash[g][hash_idx[g]++] = i;
    };

    add_point(0);
    add_point(1);

    for(int i = 2; i < n; i++){
        long long g = grid_index(p[i], N, h);
        long long mindis = dist2(p[i], p[0]), cur;
        for(int dx = -1; dx <= 1; dx++)
            for(int dy = -1; dy <= 1; dy++){
                long long gn = (g + dx*N + dy) % MOD;
                if(gn < 0) continue;
                for(int k = 0; k < hash_idx[gn]; k++){
                    cur = dist2(p[i], p[hash[gn][k]]);
                    if(cur > 8 * h2) break;
                    mindis = min(mindis, cur);
                }
            }
        
        if(mindis == 0) return 0;
        if(mindis < h2){
            for(int j = 0; j < i; j++){
                int g = grid_index(p[j], N, h) % MOD;
                hash_idx[g] = 0;
            }
            h2 = mindis;
            h = sqrt(h2);
            N = ceil(2e7 / h);
            for(int j = 0; j <= i; j++)
                add_point(j);
        } else {
            add_point(i);
        }
    }

    return h2;
}

int main(){
    int n;
    static Point p[MAXN];
    srand(time(0));

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].x += 1e7;
        p[i].y += 1e7;
    }
    random_shuffle(p, p + n);

    long long ans = nearest_dist(p, n);
    cout << ans << endl;
    return 0;
}