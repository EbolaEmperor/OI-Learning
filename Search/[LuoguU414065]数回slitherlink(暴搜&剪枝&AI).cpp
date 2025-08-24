// 以下代码完全有 ChatGPT 生成，吊打我的代码
#include <bits/stdc++.h>
using namespace std;

int m, n, startX, startY;
vector<string> g;                     // 输入的字符网格（0..3 或 * / #）

// 水平边：H[i][j] 表示顶点 (i,j)-(i,j+1) 之间是否已被选，0<=i<=m, 0<=j<n
// 垂直边：V[i][j] 表示顶点 (i,j)-(i+1,j) 之间是否已被选，0<=i<m, 0<=j<=n
bool H[8 + 1][8], V[8][8 + 1];
int  degV[8 + 1][8 + 1];             // 顶点度数，0<=i<=m, 0<=j<=n
int  num[8][8];                      // 数字格：-1 表示无数字，0..3 表示要求
int  cnt[8][8];                      // 每个格子当前已取的边数

string bestAns;
string curPath;

// 判断 (x,y) 是否是合法顶点
inline bool inVertex(int x, int y){
    return 0 <= x && x <= m && 0 <= y && y <= n;
}

// 增减一个格子的计数（若在范围内且不是无数字格）
inline void addCell(int i, int j, int delta){
    if (0 <= i && i < m && 0 <= j && j < n){
        cnt[i][j] += delta;
    }
}

// 某个数字格 (i,j) 在当前状态下“最多还能达到”的边数上界
// = 已取 + 仍可能被取（两端顶点度数都 < 2 且该边当前未被取）
int possibleMaxForCell(int i, int j){
    if (!(0 <= i && i < m && 0 <= j && j < n)) return 0;
    if (num[i][j] < 0) return 0;
    int p = cnt[i][j];
    // top: H[i][j] 连接 (i,j)-(i,j+1)
    if (!H[i][j] && degV[i][j] < 2 && degV[i][j+1] < 2) p++;
    // bottom: H[i+1][j]
    if (!H[i+1][j] && degV[i+1][j] < 2 && degV[i+1][j+1] < 2) p++;
    // left: V[i][j]
    if (!V[i][j] && degV[i][j] < 2 && degV[i+1][j] < 2) p++;
    // right: V[i][j+1]
    if (!V[i][j+1] && degV[i][j+1] < 2 && degV[i+1][j+1] < 2) p++;
    return p;
}

// 检查所有数字格的必要条件：cnt 不超过数字，且 possibleMax >= 数字
bool globalCellsFeasible(){
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            if (num[i][j] >= 0){
                if (cnt[i][j] > num[i][j]) return false;
                if (possibleMaxForCell(i, j) < num[i][j]) return false;
            }
        }
    }
    return true;
}

// 尝试沿着从 (x,y) 到 (nx,ny) 的边前进一步；成功则做增量更新并返回 true
bool stepForward(int x, int y, int nx, int ny, char ch){
    // 已在同一行或同一列
    if (!inVertex(nx, ny)) return false;

    // 确定是水平边还是垂直边，并检查是否已用过
    bool isH = (x == nx);
    int ei, ej;  // 边索引
    if (isH){
        ei = x; ej = min(y, ny);
        if (H[ei][ej]) return false;
    } else {
        ei = min(x, nx); ej = y;
        if (V[ei][ej]) return false;
    }

    // 目标顶点度数限制：除非回到起点闭环，否则只能走向“尚未入度”的顶点
    if (!(nx == startX && ny == startY)){
        if (degV[nx][ny] != 0) return false;
    }else{
        // 闭环时，起点此刻必须是端点（度数为 1），当前点也应是端点
        if (degV[startX][startY] != 1 || degV[x][y] != 1) return false;
    }

    // 选中该边
    if (isH) H[ei][ej] = true; else V[ei][ej] = true;
    degV[x][y]++; degV[nx][ny]++;

    // 相邻两个格子 +1
    if (isH){
        // 上： (ei-1, ej)；下： (ei, ej)
        if (ei > 0) addCell(ei-1, ej, +1);
        if (ei < m) addCell(ei,   ej, +1);
    }else{
        // 左： (ei, ej-1)；右： (ei, ej)
        if (ej > 0) addCell(ei, ej-1, +1);
        if (ej < n) addCell(ei, ej,   +1);
    }

    // 快速剪枝：所有数字格依然可行
    if (!globalCellsFeasible()){
        // 回滚
        if (isH){
            if (ei > 0) addCell(ei-1, ej, -1);
            if (ei < m) addCell(ei,   ej, -1);
            H[ei][ej] = false;
        }else{
            if (ej > 0) addCell(ei, ej-1, -1);
            if (ej < n) addCell(ei, ej,   -1);
            V[ei][ej] = false;
        }
        degV[x][y]--; degV[nx][ny]--;
        return false;
    }

    curPath.push_back(ch);
    return true;
}

// 回滚一步
void undoStep(int x, int y, int nx, int ny){
    bool isH = (x == nx);
    int ei, ej; 
    if (isH){ ei = x; ej = min(y, ny); }
    else    { ei = min(x, nx); ej = y; }

    if (isH){
        // 减回格子计数
        if (ei > 0) addCell(ei-1, ej, -1);
        if (ei < m) addCell(ei,   ej, -1);
        H[ei][ej] = false;
    }else{
        if (ej > 0) addCell(ei, ej-1, -1);
        if (ej < n) addCell(ei, ej,   -1);
        V[ei][ej] = false;
    }
    degV[x][y]--; degV[nx][ny]--;
    curPath.pop_back();
}

// 所有数字格是否恰好满足
bool allCellsExactlyMatch(){
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (num[i][j] >= 0 && cnt[i][j] != num[i][j])
                return false;
    return true;
}

void dfs(int x, int y){
    // 按 ASCII 字典序：D(68) < L(76) < R(82) < U(85)
    static const int dx[4] = {+1, 0, 0, -1};
    static const int dy[4] = {0, -1, +1, 0};
    static const char dc[4] = {'D','L','R','U'};

    for (int t = 0; t < 4; ++t){
        int nx = x + dx[t], ny = y + dy[t];
        char ch = dc[t];

        if (!inVertex(nx, ny)) continue;
        if (!stepForward(x, y, nx, ny, ch)) continue;

        // 若回到起点则检查是否完全满足
        if (nx == startX && ny == startY){
            if (degV[startX][startY] == 2 && allCellsExactlyMatch()){
                // 第一条找到的解就是字典序最小
                bestAns = curPath;
                return;
            }
        }else{
            // 继续扩展
            dfs(nx, ny);
            if (!bestAns.empty()) return; // 已找到
        }

        // 回溯
        undoStep(x, y, nx, ny);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    g.resize(m);
    for (int i = 0; i < m; ++i) cin >> g[i];
    cin >> startX >> startY;

    // 解析数字网格
    memset(num, -1, sizeof(num));
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            char c = g[i][j];
            if (c == '#' || c == '*') num[i][j] = -1;
            else num[i][j] = c - '0';
        }
    }

    // 初始化
    memset(H, 0, sizeof(H));
    memset(V, 0, sizeof(V));
    memset(degV, 0, sizeof(degV));
    memset(cnt, 0, sizeof(cnt));
    bestAns.clear();
    curPath.clear();

    // 搜索
    dfs(startX, startY);

    // 输出（题目保证有解；若意外未找到，则输出空串）
    cout << bestAns << '\n';
    return 0;
}