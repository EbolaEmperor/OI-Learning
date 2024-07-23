#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int T, n, h, r;
struct Point{
    int x, y, z;
} p[N];
bool mark[N];

double dist(const Point &p1, const Point &p2){
    return sqrt( (double)(p1.x - p2.x) * (p1.x - p2.x)
               + (double)(p1.y - p2.y) * (p1.y - p2.y)
               + (double)(p1.z - p2.z) * (p1.z - p2.z) );
}

void work(){
    memset(mark, 0, sizeof(mark));
    scanf("%d%d%d", &n, &h, &r);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z);
    queue<Point> q;
    for(int i = 1; i <= n; ++i)
        if(abs(p[i].z) <= r){
            q.push(p[i]);
            mark[i] = 1;
        }
    while(!q.empty()){
        Point p0 = q.front();
        for(int i = 1; i <= n; ++i)
            if(mark[i] == 0 && dist(p0, p[i]) <= 2 * r){
                mark[i] = 1;
                q.push(p[i]);
            }
        q.pop();
    }
    for(int i = 1; i <= n; ++i)
        if(p[i].z >= h-r && p[i].z <= h+r && mark[i] == 1){
            puts("Yes");
            return;
        }
    puts("No");
}

int main(){
    scanf("%d", &T);
    while(T--) work();
    return 0;
}