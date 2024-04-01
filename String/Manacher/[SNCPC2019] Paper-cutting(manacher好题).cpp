#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
vector<char> s[N], sT[N];
struct Cord{int i, j;};

void manacher(char *s, int p[]){
    static char mncs[N<<1];
    int n = strlen(s);
    for(int i = 0; i < n; i++){
        mncs[2*i] = s[i];
        if(i < n-1) mncs[2*i+1] = '#';
    }
    mncs[2*n-1] = '?';
    int r = -1, mid;
    for(int i = 0; i < 2*n-1; i++){
        p[i] = (i<=r) ? min(r-i, p[2*mid-i]) : 0;
        while(p[i] < i && mncs[i-p[i]-1]==mncs[i+p[i]+1]) p[i]++;
        if(i+p[i] > r) r = i+p[i], mid = i;
    }
}

void getfold(vector<char> s[], int n, int m, int &l, int &r){
    static int p[N<<1], fold[N<<1];
    memset(fold, 0x3f, sizeof(int)*(2*m+1));
    for(int i = 0; i < n; i++){
        manacher(&s[i][0], p);
        for(int j = 0; j < 2*m+1; j++)
            fold[j] = min(fold[j], p[j]);
    }
    l = 0; r = 2*m-2;
    for(int i = 1; i < 2*m-1; i += 2)
        if(i - fold[i] <= l) l = i + 1;
    for(int i = 2*m-3; i >= l; i -= 2)
        if(i + fold[i] >= r) r = i - 1;
    l >>= 1; r >>= 1;
}

int conn(int l, int r, int d, int u){
    int ans = 0;
    queue<Cord> q;
    static const int step[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for(int i = d; i <= u; i++)
        for(int j = l; j <= r; j++){
            if(s[i][j] == '1') continue;
            ans++;
            q.push({i,j});
            s[i][j] = '1';
            while(!q.empty()){
                Cord o = q.front(); q.pop();
                for(int k = 0; k < 4; k++){
                    Cord v = o;
                    v.i += step[k][0];
                    v.j += step[k][1];
                    if(v.i >= d && v.i <= u && v.j >= l && v.j <= r && s[v.i][v.j]=='0')
                        s[v.i][v.j] = '1', q.push(v);
                }
            }
        }
    return ans;
}

int main(){
    int T, n, m, l, r, d, u;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++){
            s[i].resize(m+1);
            scanf("%s", &s[i][0]);
        }
        for(int i = 0; i < m; i++){
            sT[i].resize(n+1);
            for(int j = 0; j < n; j++)
                sT[i][j] = s[j][i];
            sT[i][n] = '\0';
        }
        getfold(s, n, m, l, r);
        getfold(sT, m, n, d, u);
        printf("%d\n", conn(l, r, d, u));
    }
    return 0;
}