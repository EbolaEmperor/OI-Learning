#include <bits/stdc++.h>
using namespace std;

const int N = 15;
int m, n, si, sj;
int cnt[N][N];
bool vis[N][N];
bool freedom[N][N];
char path[N*N];
long long cc = 0;

bool finalCheck(){
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(!freedom[i][j] && cnt[i][j]) return false;
    return true;
}

void goup(const int &i, const int &j, const int &step, const int &dir){
    if(j) cnt[i-1][j-1] -= dir;
    if(j<n) cnt[i-1][j] -= dir;
    if(dir>0) path[step] = 'U';
    vis[i-1][j] = (dir>0);
}

void godown(const int &i, const int &j, const int &step, const int &dir){
    if(j) cnt[i][j-1] -= dir;
    if(j<n) cnt[i][j] -= dir;
    if(dir>0) path[step] = 'D';
    vis[i+1][j] = (dir>0);
}

void goleft(const int &i, const int &j, const int &step, const int &dir){
    if(i) cnt[i-1][j-1] -= dir;
    if(i<m) cnt[i][j-1] -= dir;
    if(dir>0) path[step] = 'L';
    vis[i][j-1] = (dir>0);
}

void goright(const int &i, const int &j, const int &step, const int &dir){
    if(i) cnt[i-1][j] -= dir;
    if(i<m) cnt[i][j] -= dir;
    if(dir>0) path[step] = 'R';
    vis[i][j+1] = (dir>0);
}

bool dfs(int i, int j, int step){
    if(++cc % 100000000 == 0) cout << "dfs cycle: " << cc << endl;

    if(i==si && j==sj && step){
        path[step] = '\0';
        return finalCheck();
    }

    // go down
    if(i<m && !vis[i+1][j] && (!j || cnt[i][j-1]) && (j==n || cnt[i][j])){
        if(step && j && !freedom[i][j-1] && cnt[i][j-1]==3){
            if(vis[i+1][j] || vis[i+1][j-1] || vis[i][j-1]) return false;
            godown(i, j, step, 1);
            goleft(i+1, j, step+1, 1);
            goup(i+1, j-1, step+2, 1);
            if(dfs(i, j-1, step+3)) return true;
            goup(i+1, j-1, step+2, -1);
            goleft(i+1, j, step+1, -1);
            godown(i, j, step, -1);
        } else if(step && j<n && !freedom[i][j] && cnt[i][j]==3){
            if(vis[i+1][j] || vis[i+1][j+1] || vis[i][j+1]) return false;
            godown(i, j, step, 1);
            goright(i+1, j, step+1, 1);
            goup(i+1, j+1, step+2, 1);
            if(dfs(i, j+1, step+3)) return true;
            goup(i+1, j+1, step+2, -1);
            goright(i+1, j, step+1, -1);
            godown(i, j, step, -1);
        } else if(j && !freedom[i][j-1] && cnt[i][j-1]==2){
            if(vis[i+1][j-1]) return false;
            if(vis[i][j-1]){
                godown(i, j, step, 1);
                goleft(i+1, j, step+1, 1);
                if(dfs(i+1, j-1, step+2)) return true;
                goleft(i+1, j, step+1, -1);
                godown(i, j, step, -1);
            } else {
                godown(i, j, step, 1);
                if(dfs(i+1, j, step+1)) return true;
                godown(i, j, step, -1);
            }
        } else if(j<n && !freedom[i][j] && cnt[i][j]==2){
            if(vis[i+1][j+1]) return false;
            if(vis[i][j+1]){
                godown(i, j, step, 1);
                goright(i+1, j, step+1, 1);
                if(dfs(i+1, j+1, step+2)) return true;
                goright(i+1, j, step+1, -1);
                godown(i, j, step, -1);
            } else {
                godown(i, j, step, 1);
                if(dfs(i+1, j, step+1)) return true;
                godown(i, j, step, -1);
            } 
        }else {
            godown(i, j, step, 1);
            if(dfs(i+1, j, step+1)) return true;
            godown(i, j, step, -1);
        }
    }

    // go left
    if(j && !vis[i][j-1] && (!i || cnt[i-1][j-1]) && (i==m || cnt[i][j-1])){
        if(step && i && !freedom[i-1][j-1] && cnt[i-1][j-1]==3){
            if(vis[i][j-1] || vis[i-1][j-1] || vis[i-1][j]) return false;
            goleft(i, j, step, 1);
            goup(i, j-1, step+1, 1);
            goright(i-1, j-1, step+2, 1);
            if(dfs(i-1, j, step+3)) return true;
            goright(i-1, j-1, step+2, -1);
            goup(i, j-1, step+1, -1);
            goleft(i, j, step, -1);
        } else if(step && i<m && !freedom[i][j-1] && cnt[i][j-1]==3){
            if(vis[i][j-1] || vis[i+1][j-1] || vis[i+1][j]) return false;
            goleft(i, j, step, 1);
            godown(i, j-1, step+1, 1);
            goright(i+1, j-1, step+2, 1);
            if(dfs(i+1, j, step+3)) return true;
            goright(i+1, j-1, step+2, -1);
            godown(i, j-1, step+1, -1);
            goleft(i, j, step, -1);
        } else if(i && !freedom[i-1][j-1] && cnt[i-1][j-1]==2){
            if(vis[i-1][j-1]) return false;
            if(vis[i-1][j]){
                goleft(i, j, step, 1);
                goup(i, j-1, step+1, 1);
                if(dfs(i-1, j-1, step+2)) return true;
                goup(i, j-1, step+1, -1);
                goleft(i, j, step, -1);
            } else {
                goleft(i, j, step, 1);
                if(dfs(i, j-1, step+1)) return true;
                goleft(i, j, step, -1);
            }
        } else if(i<m && !freedom[i][j-1] && cnt[i][j-1]==2){
            if(vis[i+1][j-1]) return false;
            if(vis[i+1][j]){
                goleft(i, j, step, 1);
                godown(i, j-1, step+1, 1);
                if(dfs(i+1, j-1, step+2)) return true;
                godown(i, j-1, step+1, -1);
                goleft(i, j, step, -1);
            } else {
                goleft(i, j, step, 1);
                if(dfs(i, j-1, step+1)) return true;
                goleft(i, j, step, -1);
            }
        } else {
            goleft(i, j, step, 1);
            if(dfs(i, j-1, step+1)) return true;
            goleft(i, j, step, -1);
        }
    }

    // go right
    if(j<n && !vis[i][j+1] && (!i || cnt[i-1][j]) && (i==m || cnt[i][j])){
        if(step && i && !freedom[i-1][j] && cnt[i-1][j]==3){
            if(vis[i][j+1] || vis[i-1][j+1] || vis[i-1][j]) return false;
            goright(i, j, step, 1);
            goup(i, j+1, step+1, 1);
            goleft(i-1, j+1, step+2, 1);
            if(dfs(i-1, j, step+3)) return true;
            goleft(i-1, j+1, step+2, -1);
            goup(i, j+1, step+1, -1);
            goright(i, j, step, -1);
        } else if(step && i<m && !freedom[i][j] && cnt[i][j]==3){
            if(vis[i][j+1] || vis[i+1][j+1] || vis[i+1][j]) return false;
            goright(i, j, step, 1);
            godown(i, j+1, step+1, 1);
            goleft(i+1, j+1, step+2, 1);
            if(dfs(i+1, j, step+3)) return true;
            goleft(i+1, j+1, step+2, -1);
            godown(i, j+1, step+1, -1);
            goright(i, j, step, -1);
        } else if(i && !freedom[i-1][j] && cnt[i-1][j]==2){
            if(vis[i-1][j+1]) return false;
            if(vis[i-1][j]){
                goright(i, j, step, 1);
                goup(i, j+1, step+1, 1);
                if(dfs(i-1, j+1, step+2)) return true;
                goup(i, j+1, step+1, -1);
                goright(i, j, step, -1);
            } else {
                goright(i, j, step, 1);
                if(dfs(i, j+1, step+1)) return true;
                goright(i, j, step, -1);
            }
        } else if(i<m && !freedom[i][j] && cnt[i][j]==2){
            if(vis[i+1][j+1]) return false;
            if(vis[i+1][j]){
                goright(i, j, step, 1);
                godown(i, j+1, step+1, 1);
                if(dfs(i+1, j+1, step+2)) return true;
                godown(i, j+1, step+1, -1);
                goright(i, j, step, -1);
            } else {
                goright(i, j, step, 1);
                if(dfs(i, j+1, step+1)) return true;
                goright(i, j, step, -1);
            }
        } else {
            goright(i, j, step, 1);
            if(dfs(i, j+1, step+1)) return true;
            goright(i, j, step, -1);
        }
    }

    // go up
    if(i && !vis[i-1][j] && (!j || cnt[i-1][j-1]) && (j==n || cnt[i-1][j])){
        if(step && j && !freedom[i-1][j-1] && cnt[i-1][j-1]==3){
            if(vis[i-1][j] || vis[i-1][j-1] || vis[i][j-1]) return false;
            goup(i, j, step, 1);
            goleft(i-1, j, step+1, 1);
            godown(i-1, j-1, step+2, 1);
            if(dfs(i, j-1, step+3)) return true;
            godown(i-1, j-1, step+2, -1);
            goleft(i-1, j, step+1, -1);
            goup(i, j, step, -1);
        } else if(step && j<n && !freedom[i-1][j] && cnt[i-1][j]==3){
            if(vis[i-1][j] || vis[i-1][j+1] || vis[i][j+1]) return false;
            goup(i, j, step, 1);
            goright(i-1, j, step+1, 1);
            godown(i-1, j+1, step+2, 1);
            if(dfs(i, j+1, step+3)) return true;
            godown(i-1, j+1, step+2, -1);
            goright(i-1, j, step+1, -1);
            goup(i, j, step, -1);
        } else if(j && !freedom[i-1][j-1] && cnt[i-1][j-1]==2){
            if(vis[i-1][j-1]) return false;
            if(vis[i][j-1]){
                goup(i, j, step, 1);
                goleft(i-1, j, step+1, 1);
                if(dfs(i-1, j-1, step+2)) return true;
                goleft(i-1, j, step+1, -1);
                goup(i, j, step, -1);
            } else {
                goup(i, j, step, 1);
                if(dfs(i-1, j, step+1)) return true;
                goup(i, j, step, -1);
            }
        } else if(j<n && !freedom[i-1][j] && cnt[i-1][j]==2){
            if(vis[i-1][j+1]) return false;
            if(vis[i][j+1]){
                goup(i, j, step, 1);
                goright(i-1, j, step+1, 1);
                if(dfs(i-1, j+1, step+2)) return true;
                goright(i-1, j, step+1, -1);
                goup(i, j, step, -1);
            } else {
                goup(i, j, step, 1);
                if(dfs(i-1, j, step+1)) return true;
                goup(i, j, step, -1);
            }
        } else {
            goup(i, j, step, 1);
            if(dfs(i-1, j, step+1)) return true;
            goup(i, j, step, -1);
        }
    }

    return false;
}

int main(){
    cin >> m >> n;
    string s;
    for(int i = 0; i < m; i++){
        cin >> s;
        for(int j = 0; j < n; j++){
            if(s[j] == '#') freedom[i][j] = true, cnt[i][j] = 4;
            else freedom[i][j] = false, cnt[i][j] = s[j]-'0';
        }
    }
    cin >> si >> sj;
    bool success = dfs(si, sj, 0);
    puts(success ? path : "no solution");
    cerr << "dfs for " << cc << " times" << endl;
    return 0;
}