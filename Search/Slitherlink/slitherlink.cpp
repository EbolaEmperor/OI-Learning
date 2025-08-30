#include <bits/stdc++.h>
using namespace std;

// ===== 全局尺寸（供 ID 宏使用） =====
int n, m;

// ===== 邻接偏移 =====
const int adj4[][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};
const int adj8[][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

#define ID(ii, jj) ((size_t)(ii) * (size_t)(m + 2) + (size_t)(jj))
#define FORCELL0 for (int i = 0; i <= n+1; i++) \
                 for (int j = 0; j <= m+1; j++)
#define FORCELL for (int i = 1; i <= n; i++) \
                for (int j = 1; j <= m; j++)
#define CUR now[ID(i,j)]
#define TAR now[ID(i0,j0)]
#define ADJ (now[ID(ADJX, ADJY)])
#define ADJX (i + adj4[k][0])
#define ADJY (j + adj4[k][1])
#define INBOARD(i,j) (i > 0 && i <= n && j > 0 && j <= m)
#define ADJCORD (cord(ADJX, ADJY))
#define FORADJ4 for (int k = 0; k < 4; k++) \
                if (ADJX >= 0 && ADJX <= n+1 && ADJY >= 0 && ADJY <= m+1)
#define FORADJ8 for (int k = 0; k < 8; k++)
#define ADJ8X(v) (i + adj8[v][0])
#define ADJ8Y(v) (j + adj8[v][1])
#define ADJ8(v) ADJ8X(v),ADJ8Y(v)

// ===== 类型与全局变量 =====
enum Status : uint8_t {
    UNKNOWN, INNER, OUTER, UNKNOWN_BFS, INNER_BFS, OUTER_BFS
};
typedef pair<int,int> cord;
typedef vector<Status> Slither;

vector<string> board;
Slither finalAns;

// ===== 工具函数 =====
static inline Slither newSlither() {
    // 一维数组，默认 UNKNOWN；边界设为 OUTER
    Slither ret((size_t)(n + 2) * (m + 2), UNKNOWN);
    for (int j = 0; j <= m + 1; ++j) {
        ret[ID(0, j)]     = OUTER;
        ret[ID(n + 1, j)] = OUTER;
    }
    for (int i = 1; i <= n; ++i) {
        ret[ID(i, 0)]     = OUTER;
        ret[ID(i, m + 1)] = OUTER;
    }
    return ret;
}

static inline void addBoundary(const vector<string> &_board) {
    n = (int)_board.size();
    m = (int)_board[0].size();
    board.clear();
    board.reserve(n + 2);

    string border(m + 2, '.');
    board.push_back(border);
    for (int i = 0; i < n; ++i) {
        string row; row.reserve(m + 2);
        row.push_back('.');
        row += _board[i];
        row.push_back('.');
        board.push_back(std::move(row));
    }
    board.push_back(border);
}

// 寻找 now 里面第一个为 sta 的状态
static inline cord findFirst(const Slither &now, Status sta) {
    FORCELL{
        if (now[ID(i,j)] == sta)
            return cord(i, j);
    }
    return cord(-1,-1);
}

// 检查数字周围是否有正确数量的线
static inline bool checkNumber(const Slither &now) {
    FORCELL {
        char c = board[i][j];
        if (c == '.') continue;
        int cnt = 0, lim = c - '0';
        FORADJ4 {
            if (now[ID(i,j)] != now[ID(ADJX,ADJY)]) ++cnt;
        }
        if (cnt != lim) return false;
    }
    return true;
}

// 检查 INNER 区域是否构成一个连通块（不改 now，visited 单独存）
static inline bool isConnected(const Slither& now) {
    auto [i0, j0] = findFirst(now, INNER);
    if (i0 == -1) return true; // 没 INNER 视作连通

    const int H = n + 2, W = m + 2;
    auto lid = [&](int x, int y){ return (size_t)x * W + y; };
    vector<uint8_t> vis((size_t)H * W, 0);

    deque<cord> q;
    q.emplace_back(i0, j0);
    vis[lid(i0, j0)] = 1;

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop_front();
        for (int k = 0; k < 4; ++k) {
            int ni = i + adj4[k][0], nj = j + adj4[k][1];
            if (ni >= 1 && ni <= n && nj >= 1 && nj <= m) {
                if (!vis[lid(ni, nj)] && now[ID(ni, nj)] == INNER) {
                    vis[lid(ni, nj)] = 1;
                    q.emplace_back(ni, nj);
                }
            }
        }
    }

    FORCELL {
        if (now[ID(i,j)] == INNER && !vis[lid(i, j)]) return false;
    }
    return true;
}

// 检查是否有 OUTER 被 INNER 包起来形成一个洞
// 如果有 UNKNOWN 被 INNER 包起来，那就把它设为 INNER
static inline bool checkHole(Slither &now) {
    queue<cord> q;
    q.emplace(0, 0);
    now[ID(0,0)] = OUTER_BFS;
    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        FORADJ4 {
            Status &adj = now[ID(ADJX,ADJY)];
            if (adj == UNKNOWN) {
                adj = UNKNOWN_BFS;
                q.emplace(ADJX, ADJY);
            } else if(adj == OUTER) {
                adj = OUTER_BFS;
                q.emplace(ADJX, ADJY);
            }
        }
    }
    FORCELL0 {
        Status &cur = now[ID(i,j)];
        if (cur == OUTER) return false;
        else if (cur == UNKNOWN) cur = INNER;
        else if (cur == UNKNOWN_BFS) cur = UNKNOWN;
        else if (cur == OUTER_BFS) cur = OUTER;
    }
    return true;
}

static inline bool setStatus(Slither &now, int i, int j, Status sta) {
    Status &cur = now[ID(i,j)];
    if (cur == UNKNOWN) {
        cur = sta;
        return true;
    } else {
        return cur == sta;
    }
}

static inline Status diff(Status sta) {
    return sta == INNER ? OUTER : INNER;
}

static inline bool makeSame(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    Status &tar = now[ID(i0,j0)];
    if (tar != UNKNOWN) {
        Status &cur = now[ID(i,j)];
        if (cur == UNKNOWN) {
            cur = tar;
            cg = true;
            return true;
        } else {
            return cur == tar;
        }
    }
    return true;
}

static inline bool makeDiff(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    Status &tar = now[ID(i0,j0)];
    if (tar != UNKNOWN) {
        Status &cur = now[ID(i,j)];
        if (cur == UNKNOWN) {
            cur = diff(tar);
            cg = true;
            return true;
        } else {
            return cur != tar;
        }
    }
    return true;
}

static inline bool assertSame(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    return makeSame(now, i, j, i0, j0, cg) && makeSame(now, i0, j0, i, j, cg);
}

static inline bool assertDiff(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    return makeDiff(now, i, j, i0, j0, cg) && makeDiff(now, i0, j0, i, j, cg);
}

static inline bool isSame(const Slither &now, int i, int j, int i0, int j0) {
    Status a = now[ID(i,j)], b = now[ID(i0,j0)];
    return a != UNKNOWN && b != UNKNOWN && a == b;
}

static inline bool isDiff(const Slither &now, int i, int j, int i0, int j0) {
    Status a = now[ID(i,j)], b = now[ID(i0,j0)];
    return a != UNKNOWN && b != UNKNOWN && a != b;
}

static inline bool applyRules(Slither &now) {
    bool cg = true;
    auto [i0, j0] = findFirst(now, UNKNOWN);
    while(cg) {
        cg = false;
        for (int i = max(1, i0-1); i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = board[i][j];

            // 数字 0 必须和他周围四个格子在同一个 region 里
            if (c == '0')
                FORADJ4 if(!assertSame(now, i, j, ADJX, ADJY, cg))
                    return false;

            if (now[ID(i,j)] != UNKNOWN && c != '.') {
                // 检查有数字的位置，如果线连满了，就把其余的线设为不连接
                int cnt = 0, lim = c - '0';
                FORADJ4 {
                    if (now[ID(ADJX,ADJY)] != UNKNOWN && now[ID(i,j)] != now[ID(ADJX,ADJY)]) ++cnt;
                }
                if (cnt > lim) return false;
                if (cnt == lim) {
                    FORADJ4 {
                        if (now[ID(ADJX,ADJY)] == UNKNOWN)
                            setStatus(now, ADJX, ADJY, now[ID(i,j)]);
                    }
                }

                // 检查有数字的位置，如果未连的线达到 4-lim，就把其余的线设为连接
                cnt = 0;
                FORADJ4 {
                    if (now[ID(ADJX,ADJY)] != UNKNOWN && now[ID(i,j)] == now[ID(ADJX,ADJY)]) ++cnt;
                }
                if (cnt > 4 - lim) return false;
                if (cnt == 4 - lim) {
                    FORADJ4 {
                        if (now[ID(ADJX,ADJY)] == UNKNOWN)
                            setStatus(now, ADJX, ADJY, diff(now[ID(i,j)]));
                    }
                }
            }

            // 检查连线是否出现十字交叉
            if (isDiff(now, i, j, i+1, j) && isDiff(now, i, j, i, j+1))
                if (!assertDiff(now, i, j, i+1, j+1, cg)) return false;

            if (isDiff(now, i, j, i, j+1) && isDiff(now, i, j+1, i+1, j+1))
                if (!assertSame(now, i, j, i+1, j, cg)) return false;

            if (isDiff(now, i, j, i+1, j) && isDiff(now, i+1, j, i+1, j+1))
                if (!assertSame(now, i, j, i, j+1, cg)) return false;

            if (isDiff(now, i+1, j, i+1, j+1) && isDiff(now, i, j+1, i+1, j+1))
                if (!assertSame(now, i, j, i+1, j, cg)) return false;

            if (c == '1') {
                for(int k = 0; k < 8; k += 2) {
                    // 如果有一条线从 1 的右下角进来，且没有立刻离开，则它的左边、上边不能连线。其它三个角同理
                    if (isDiff(now, ADJ8(k), ADJ8(k+1)) && isSame(now, ADJ8(k+1), ADJ8(k+2)) ||
                        isSame(now, ADJ8(k), ADJ8(k+1)) && isDiff(now, ADJ8(k+1), ADJ8(k+2))) {
                        if (!assertSame(now, i, j, ADJ8(k+4), cg) || !assertSame(now, i, j, ADJ8(k+6), cg))
                            return false;
                    }

                    // 如果有一条线从 1 的右下角进来，且已确定它的左边、上边没有连线，则这条线不能立刻离开，必须绕着 1 走一步
                    if (isSame(now, i, j, ADJ8(k+4)) && isSame(now, i, j, ADJ8(k+6))) {
                        if (isDiff(now, ADJ8(k), ADJ8(k+1)) && !assertSame(now, ADJ8(k+1), ADJ8(k+2), cg))
                            return false;
                        if (isDiff(now, ADJ8(k+1), ADJ8(k+2)) && !assertSame(now, ADJ8(k), ADJ8(k+1), cg))
                            return false;
                    }

                    /*
                        .    
                        x    
                    +[x]+ x .
                      1[x]    
                        +   .
                     */
                    if (isSame(now, ADJ8(k), ADJ8(k+1)) && isSame(now, ADJ8(k+1), ADJ8(k+2))) {
                        if (!assertSame(now, i, j, ADJ8(k), cg) || !assertSame(now, i, j, ADJ8(k+2), cg))
                            return false;
                    }

                    //         +     +     +     +     +                    +     +     +     +     +  
                    //                  1                                            1                 
                    //         +     +     +  x  +     +         =>         +     +  x  +  x  +     +  
                    //                  1                                            1                 
                    //         +     +     +     +     +                    +     +     +     +     +
                    if (board[ADJ8X(k+2)][ADJ8Y(k+2)] == '1' && isSame(now, ADJ8(k), ADJ8(k+1))) {
                        if (!assertSame(now, i, j, ADJ8(k+2), cg)) return false;
                    }
                }
            }

            //        +     +     +     +     +     +                    +     +     +     +     +     +  
            //                                                                       x                    
            //        +     +     +     +     +     +                    +     +  x  +  -  +     +     +  
            //                       3                        =>                     |  3                 
            //        +     +     +     +     +     +                    +     +     +     +  x  +     +  
            //                          |                                                  |              
            //        +     +     +     +     +     +                    +     +     +     +     +     +  
            if (c == '3') {
                for(int k = 0; k < 8; k += 2) {
                    if (isDiff(now, ADJ8(k), ADJ8(k+1))) {
                        if (!assertSame(now, ADJ8(k+1), ADJ8(k+2), cg) || !assertDiff(now, i, j, ADJ8(k+4), cg) || !assertDiff(now, i, j, ADJ8(k+6), cg) ||
                            !assertSame(now, ADJ8(k+4), ADJ8(k+5), cg) || !assertSame(now, ADJ8(k+5), ADJ8(k+6), cg))
                                return false;
                    } else if (isDiff(now, ADJ8(k+1), ADJ8(k+2))) {
                        if (!assertSame(now, ADJ8(k), ADJ8(k+1), cg) || !assertDiff(now, i, j, ADJ8(k+4), cg) || !assertDiff(now, i, j, ADJ8(k+6), cg) ||
                            !assertSame(now, ADJ8(k+4), ADJ8(k+5), cg) || !assertSame(now, ADJ8(k+5), ADJ8(k+6), cg))
                                return false;
                    }
                }
            }

            //         +     +  -  +     +     +     +                    +     +  -  +     +     +     +  
            //                        3                        =>               x        3                 
            //         +     +  -  +     +     +     +                    +     +  -  +     +     +     + 
            if (c == '3') {
                if (isDiff(now, i, j-1, i-1, j-1) && isDiff(now, i, j-1, i+1, j-1)) {
                    if (!assertSame(now, i, j-1, i, j-2, cg)) return false;
                }
                if (isDiff(now, i, j+1, i-1, j+1) && isDiff(now, i, j+1, i+1, j+1)) {
                    if (!assertSame(now, i, j+1, i, j+2, cg)) return false;
                }
                if (isDiff(now, i-1, j, i-1, j-1) && isDiff(now, i-1, j, i-1, j+1)) {
                    if (!assertSame(now, i-1, j, i-2, j, cg)) return false;
                }
                if (isDiff(now, i+1, j, i+1, j-1) && isDiff(now, i+1, j, i+1, j+1)) {
                    if (!assertSame(now, i+1, j, i+2, j, cg)) return false;
                }
            }

            /*
                .   .   .
                    x 
                +   +   +  
                | 3 | 3 | 
                +   +   +
                    x   
                .   .   .
            */
            if (c == '3' && board[i][j+1] == '3') {
                if (now[ID(i,j)] != UNKNOWN || now[ID(i,j-1)] != UNKNOWN || now[ID(i,j+1)] != UNKNOWN || now[ID(i,j+2)] != UNKNOWN) {
                    if (!assertDiff(now, i, j-1, i, j, cg) || !assertSame(now, i, j-1, i, j+1, cg) || !assertDiff(now, i, j-1, i, j+2, cg) ||
                        !assertDiff(now, i, j, i, j+1, cg) || !assertSame(now, i, j, i, j+2, cg) || !assertDiff(now, i, j+1, i, j+2, cg) ||
                        !assertSame(now, i-1, j, i-1, j+1, cg) || !assertSame(now, i+1, j, i+1, j+1, cg))
                        return false;
                }
            }
            if (c == '3' && board[i+1][j] == '3') {
                if (now[ID(i,j)] != UNKNOWN || now[ID(i-1,j)] != UNKNOWN || now[ID(i+1,j)] != UNKNOWN || now[ID(i+2,j)] != UNKNOWN) {
                    if (!assertDiff(now, i-1, j, i, j, cg) || !assertSame(now, i-1, j, i+1, j, cg) || !assertDiff(now, i-1, j, i+2, j, cg) ||
                        !assertDiff(now, i, j, i+1, j, cg) || !assertSame(now, i, j, i+2, j, cg) || !assertDiff(now, i+1, j, i+2, j, cg) ||
                        !assertSame(now, i, j-1, i+1, j-1, cg) || !assertSame(now, i, j+1, i+1, j+1, cg))
                        return false;
                }
            }

            /*
                    +---+  
                      3 | 
                +   .   +
                | 3     
                +---+   .
            */
            if (c == '3' && board[i+1][j-1] == '3') {
                if (!assertDiff(now, i, j, i-1, j, cg) || 
                    !assertDiff(now, i, j, i, j+1, cg) || 
                    !assertDiff(now, i+1, j-1, i+1, j-2, cg) ||
                    !assertDiff(now, i+1, j-1, i+2, j-1, cg)) {
                        return false;
                }
            }

            /*
                +---+   .  
                | 3       
                +   .   +
                      3 |
                .   +---+
            */
            if (c == '3' && board[i+1][j+1] == '3') {
                if (!assertDiff(now, i, j, i-1, j, cg) || 
                    !assertDiff(now, i, j, i, j-1, cg) || 
                    !assertDiff(now, i+1, j+1, i+1, j+2, cg) ||
                    !assertDiff(now, i+1, j+1, i+2, j+1, cg)) {
                        return false;
                }
            }

            if (c == '3') {
                /*
                        .    
                        x    
                    +[-]+ x .
                      3[|]    
                        +   .
                */
                for (int k = 0; k < 8; k += 2)
                    if (isSame(now, ADJ8(k), ADJ8(k+1)) && isSame(now, ADJ8(k+1), ADJ8(k+2))) {
                        if (!assertDiff(now, i, j, ADJ8(k), cg) || !assertDiff(now, i, j, ADJ8(k+2), cg))
                            return false;
                    }
            }

             /*
                    .   .  
                    | 3  
                . x +---+
                x 0 x   
                . x .   .
            */
            if (c == '3') {
                for (int k = 0; k < 8; k += 2) {
                    if (board[ADJ8X(k+1)][ADJ8Y(k+1)] != '0') continue;
                    if (!assertDiff(now, i, j, ADJ8(k), cg) || !assertDiff(now, i, j, ADJ8(k+2), cg))
                        return false;
                }
            }

            /*
                    . x .  
                      1 x 
                .   .   .
               [x]1     
                .[x].   .
            */
            if (c == '1' && board[i+1][j-1] == '1') {
                if (isSame(now, i, j, i-1, j) && isSame(now, i, j, i, j+1)) {
                    if (!assertSame(now, i+1, j-1, i+1, j-2, cg) || !assertSame(now, i+1, j-1, i+2, j-1, cg))
                        return false;
                }
                if (isSame(now, i+1, j-1, i+1, j-2) && isSame(now, i+1, j-1, i+2, j-1)) {
                    if (!assertSame(now, i, j, i-1, j, cg) || !assertSame(now, i, j, i, j+1, cg))
                        return false;
                }
            }

            /*
                . x .   .  
                x 1       
                .   .   .
                      1[x]   
                .   .[x].
            */
            if (c == '1' && board[i+1][j+1] == '1') {
                if (isSame(now, i, j, i-1, j) && isSame(now, i, j, i, j-1)) {
                    if (!assertSame(now, i+1, j+1, i+1, j+2, cg) || !assertSame(now, i+1, j+1, i+2, j+1, cg))
                        return false;
                }
                if (isSame(now, i+1, j+1, i+1, j+2) && isSame(now, i+1, j+1, i+2, j+1)) {
                    if (!assertSame(now, i, j, i-1, j, cg) || !assertSame(now, i, j, i, j-1, cg))
                        return false;
                }
            }
        }
    }

    return true;
}

static inline void initalRules(Slither &now) {
    // 如果 3 出现在角落里，则必为 INNER
    if (board[1][1] == '3') setStatus(now, 1, 1, INNER);
    if (board[1][m] == '3') setStatus(now, 1, m, INNER);
    if (board[n][1] == '3') setStatus(now, n, 1, INNER);
    if (board[n][m] == '3') setStatus(now, n, m, INNER);

    // 如果 1 出现在角落里，则必为 OUTER
    if (board[1][1] == '1') setStatus(now, 1, 1, OUTER);
    if (board[1][m] == '1') setStatus(now, 1, m, OUTER);
    if (board[n][1] == '1') setStatus(now, n, 1, OUTER);
    if (board[n][m] == '1') setStatus(now, n, m, OUTER);

    // 角落的 1 组合
    if (board[1][1] == '1' && board[2][1] == '1') setStatus(now, 2, 1, OUTER), setStatus(now, 1, 2, INNER);
    if (board[1][1] == '1' && board[1][2] == '1') setStatus(now, 2, 1, INNER), setStatus(now, 1, 2, OUTER);
    if (board[1][m] == '1' && board[2][m] == '1') setStatus(now, 2, m, OUTER), setStatus(now, 1, m-1, INNER);
    if (board[1][m] == '1' && board[1][m-1] == '1') setStatus(now, 2, m, INNER), setStatus(now, 1, m-1, OUTER);
    if (board[n][1] == '1' && board[n-1][1] == '1') setStatus(now, n-1, 1, OUTER), setStatus(now, n, 2, INNER);
    if (board[n][1] == '1' && board[n][2] == '1') setStatus(now, n-1, 1, INNER), setStatus(now, n, 2, OUTER);
    if (board[n][m] == '1' && board[n-1][m] == '1') setStatus(now, n-1, m, OUTER), setStatus(now, n, m-1, INNER);
    if (board[n][m] == '1' && board[n][m-1] == '1') setStatus(now, n-1, m, INNER), setStatus(now, n, m-1, OUTER);

    // 如果 0 出现在角落里，则它和周围两格必为 OUTER
    if (board[1][1] == '0') setStatus(now, 1, 1, OUTER), setStatus(now, 1, 2, OUTER),   setStatus(now, 2, 1, OUTER);
    if (board[1][m] == '0') setStatus(now, 1, m, OUTER), setStatus(now, 1, m-1, OUTER), setStatus(now, 2, m, OUTER);
    if (board[n][1] == '0') setStatus(now, n, 1, OUTER), setStatus(now, n-1, 1, OUTER), setStatus(now, n, 2, OUTER);
    if (board[n][m] == '0') setStatus(now, n, m, OUTER), setStatus(now, n-1, m, OUTER), setStatus(now, n, m-1, OUTER);

    // 如果 2 出现在角落里，则周围两格必为 INNER，它自己不一定
    if (board[1][1] == '2') setStatus(now, 1, 2, INNER),   setStatus(now, 2, 1, INNER);
    if (board[1][m] == '2') setStatus(now, 1, m-1, INNER), setStatus(now, 2, m, INNER);
    if (board[n][1] == '2') setStatus(now, n-1, 1, INNER), setStatus(now, n, 2, INNER);
    if (board[n][m] == '2') setStatus(now, n-1, m, INNER), setStatus(now, n, m-1, INNER);
}

static bool solve(Slither now) {
    if (!applyRules(now)) return false;
    if (!checkHole(now)) return false;

    auto [i, j] = findFirst(now, UNKNOWN);
    if (i == -1) {
        if (checkNumber(now) && isConnected(now)) {
            finalAns = std::move(now);
            return true;
        } else {
            return false;
        }
    }

    auto nxt = (rand() & 1) ? INNER : OUTER;
    now[ID(i,j)] = nxt;
    if (solve(now)) return true;
    now[ID(i,j)] = diff(nxt);
    if (solve(now)) return true;
    return false;
}

// === 输出字符画 ===
static void print_solution_ascii(const vector<string>& puzzle, const Slither& solved) {
    int n = (int)puzzle.size();
    int m = (int)puzzle[0].size();
    auto is_diff_region = [](Status a, Status b) { return a != b;};

    vector<string> buf(2 * n + 3, string(4 * m + 5, ' '));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c = puzzle[i - 1][j - 1];
            buf[2 * i][4 * j] = (c == '.' ? ' ' : c);
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (is_diff_region(solved[ID(i,j)], solved[ID(i + 1, j)])) {
                buf[2 * i + 1][4 * j - 1] = '-';
                buf[2 * i + 1][4 * j]     = '-';
                buf[2 * i + 1][4 * j + 1] = '-';
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (is_diff_region(solved[ID(i,j)], solved[ID(i, j + 1)])) {
                buf[2 * i][4 * j + 2] = '|';
            }
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int cnt_h = 0, cnt_v = 0;
            if (buf[2 * i + 1][4 * j + 1] == '-') ++cnt_h;
            if (buf[2 * i + 1][4 * j + 3] == '-') ++cnt_h;
            if (buf[2 * i][4 * j + 2] == '|')     ++cnt_v;
            if (buf[2 * i + 2][4 * j + 2] == '|') ++cnt_v;

            char &ch = buf[2 * i + 1][4 * j + 2];
            if (cnt_h == 2) ch = '-';
            else if (cnt_v == 2) ch = '|';
            else if (cnt_h == 1 && cnt_v == 1) ch = '+';
            else ch = '.';
        }
    }

    for (int i = 0; i < (int)buf.size(); ++i) {
        cout << buf[i] << '\n';
    }
}

// === 入口 ===
vector<string> Slitherlink(vector<string> _board){
    addBoundary(_board);
    auto slither = newSlither();
    initalRules(slither);
    if (solve(slither)) {
        auto ans = _board;
        FORCELL{
            ans[i-1][j-1] = (finalAns[ID(i,j)] == INNER) ? '*' : '.';
        }
        #ifdef LOCAL
        print_solution_ascii(_board, finalAns);
        #endif
        return ans;
    } else {
        cerr << "Slitherlink: no solution." << endl;
        return vector<string>();
    }
}