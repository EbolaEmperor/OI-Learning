#include <bits/stdc++.h>
using namespace std;

int n;
string str[10];
int p[10][52][2];
// p[i][c][k]: 字母 c 在第 i 个字符串中第 k+1 次出现的位置

const int N = 1024 * 52;
int f[N], pre[N];

int mapping(char c){
    if(c >= 'a' && c <= 'z') return c - 'a';
    else return c - 'A' + 26;
}

char invmapping(int x){
    if(x < 26) return 'a' + x;
    else return 'A' + (x - 26);
}

void output(int u){
    if(pre[u] >= 0) output(pre[u]);
    putchar(invmapping(u >> 10));
}

void work(){
    memset(p, -1, sizeof(p));
    memset(pre, -1, sizeof(pre));
    memset(f, 0, sizeof(f));
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> str[i];
        static int cnt[52];
        memset(cnt, 0, sizeof(cnt));
        for(int j = 0; j < str[i].size(); j++){
            str[i][j] = mapping(str[i][j]);
            p[i][str[i][j]][cnt[str[i][j]]++] = j;
        }
    }
    for(int pos = 0; pos < str[0].size(); pos++)
        for(int s = 0; s < (1<<n); s++){
            int c = str[0][pos];
            if(pos != p[0][c][s&1]) continue;
            int u = c << 10 | s;
            bool flag = true;
            for(int j = 0; j < n; j++)
                if(p[j][c][s>>j&1] == -1) flag = false;
            if(!flag) continue;
            if(!f[u]) f[u] = 1;
            for(int nxt = pos + 1; nxt < str[0].size(); nxt++){
                int nc = str[0][nxt];
                int ns = (nxt == p[0][nc][0]) ? 0 : 1;
                for(int j = 1; j < n; j++){
                    if(p[j][nc][0] > p[j][c][s>>j&1]) ns |= 0;
                    else if(p[j][nc][1] > p[j][c][s>>j&1]) ns |= 1<<j;
                    else { ns = -1; break; }
                }
                if(ns >= 0){
                    int v = nc << 10 | ns;
                    if(f[u] + 1 > f[v]){
                        f[v] = f[u] + 1;
                        pre[v] = u;
                    }
                }
            }
        }
    int maxu = -1;
    for(int i = 0; i < N; i++)
        if(f[i] && (maxu == -1 || f[i] > f[maxu])) maxu = i;
    if(maxu == -1) printf("0\n\n");
    else printf("%d\n", f[maxu]), output(maxu), puts("");
}

int main(){
    int t;
    cin >> t;
    while(t--) work();
    return 0;
}
