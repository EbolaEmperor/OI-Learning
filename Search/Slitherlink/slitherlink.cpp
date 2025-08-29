#include <bits/stdc++.h>
using namespace std;

#define FORCELL0 for (int i = 0; i <= n+1; i++) \
                 for (int j = 0; j <= m+1; j++)
#define FORCELL for (int i = 1; i <= n; i++) \
                for (int j = 1; j <= m; j++)
#define CUR now[i][j]
#define TAR now[i0][j0]
#define ADJ (now[i + adj4[k][0]][j + adj4[k][1]])
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

const int adj4[][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};
const int adj8[][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

vector<string> board;
int n, m;

enum Status {
    UNKNOWN, INNER, OUTER, UNKNOWN_BFS, INNER_BFS, OUTER_BFS
};
typedef pair<int,int> cord;
typedef vector<vector<Status>> Slither;
Slither finalAns;

Slither newSlither() {
    vector<Status> line(m + 2);
    line[0] = line[m+1] = OUTER;
    vector<Status> bdLine(m + 2, OUTER);
    Slither ret(n + 2);
    ret[0] = ret[n+1] = bdLine;
    for (int i = 1; i <= n; i++) ret[i] = line;
    return ret;
}

void addBoundary(const vector<string> &_board) {
    n = _board.size();
    m = _board[0].size();
    board.resize(n + 2);
    for (int i = 0; i <= m+1; i++) {
        board[0] += ".";
    }
    board[n+1] = board[0];
    for (int i = 1; i <= n; i++) {
        board[i] = ".";
        board[i] += _board[i-1];
        board[i] += ".";
    }
}

// 寻找 now 里面第一个为 sta 的状态
cord findFirst(const Slither &now, Status sta) {
    FORCELL{
        if (now[i][j] == sta)
            return cord(i, j);
    }
    return cord(-1,-1);
}

// 检查数字周围是否有正确数量的线
bool checkNumber(const Slither &now) {
    FORCELL {
        if (board[i][j] == '.') continue;
        int cnt = 0;
        FORADJ4 {
            if (CUR != ADJ) ++cnt;
        }
        if (cnt != board[i][j] - '0') return false;
    }
    return true;
}

// 检查 INNER 区域是否构成一个连通块
bool isConnected(Slither now) {
    queue<cord> q;
    q.push(findFirst(now, INNER));
    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        CUR = INNER_BFS;
        FORADJ4 {
            if (ADJ == INNER) q.push(ADJCORD);
        }
    }
    FORCELL {
        if (CUR == INNER) return false;
    }
    return true;
}

// 检查是否有 OUTER 被 INNER 区域包起来形成一个洞
// 如果有 UNKNOWN 被 INNER 包起来，那就把它设为 INNER
bool checkHole(Slither &now) {
    queue<cord> q;
    q.push(cord(0, 0));
    while(!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (CUR == UNKNOWN) {
            CUR = UNKNOWN_BFS;
        } else if(CUR == OUTER) {
            CUR = OUTER_BFS;
        }
        FORADJ4 {
            if (ADJ == UNKNOWN || ADJ == OUTER)
                q.push(ADJCORD);
        }
    }
    FORCELL0 {
        if (CUR == OUTER) return false;
        else if (CUR == UNKNOWN) CUR = INNER;
        else if (CUR == UNKNOWN_BFS) CUR = UNKNOWN;
        else if (CUR == OUTER_BFS) CUR = OUTER;
    }
    return true;
}

bool setStatus(Slither &now, int i, int j, Status sta) {
    if (CUR == UNKNOWN) {
        CUR = sta;
        return true;
    } else {
        return CUR == sta;
    }
}

bool makeSame(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    if (TAR != UNKNOWN) {
        if (CUR == UNKNOWN) {
            CUR = TAR;
            cg = true;
            return true;
        } else {
            return CUR == TAR;
        }
    }
    return true;
}

inline Status diff(Status sta) {
    return sta == INNER ? OUTER : INNER;
}

bool makeDiff(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    if (TAR != UNKNOWN) {
        if (CUR == UNKNOWN) {
            CUR = diff(TAR);
            cg = true;
            return true;
        } else {
            return CUR != TAR;
        }
    }
    return true;
}

inline bool assertSame(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    return makeSame(now, i, j, i0, j0, cg) && makeSame(now, i0, j0, i, j, cg);
}

inline bool assertDiff(Slither &now, int i, int j, int i0, int j0, bool &cg) {
    return makeDiff(now, i, j, i0, j0, cg) && makeDiff(now, i0, j0, i, j, cg);
}

inline bool isSame(const Slither &now, int i, int j, int i0, int j0) {
    return CUR != UNKNOWN && TAR != UNKNOWN && CUR == TAR;
}

inline bool isDiff(const Slither &now, int i, int j, int i0, int j0) {
    return CUR != UNKNOWN && TAR != UNKNOWN && CUR != TAR;
}

bool applyRules(Slither &now) {
    bool cg = true;
    while(cg) {
        cg = false;

        FORCELL {
            // 数字 0 必须和他周围四个格子在同一个 region 里
            if (board[i][j] == '0')
                FORADJ4 if(!assertSame(now, i, j, ADJX, ADJY, cg))
                    return false;

            if (CUR != UNKNOWN && board[i][j] != '.') {
                // 检查有数字的位置，如果线连满了，就把其余的线设为不连接
                int cnt = 0, lim = board[i][j] - '0';
                FORADJ4 {
                    if (ADJ != UNKNOWN && CUR != ADJ) ++cnt;
                }
                if (cnt > lim) return false;
                if (cnt == lim) {
                    FORADJ4 {
                        if (ADJ == UNKNOWN)
                            setStatus(now, ADJX, ADJY, CUR);
                    }
                }

                // 检查有数字的位置，如果未连的线达到 4-lim，就把其余的线设为连接
                cnt = 0;
                FORADJ4 {
                    if (ADJ != UNKNOWN && CUR == ADJ) ++cnt;
                }
                if (cnt > 4 - lim) return false;
                if (cnt == 4 - lim) {
                    FORADJ4 {
                        if (ADJ == UNKNOWN)
                            setStatus(now, ADJX, ADJY, diff(CUR));
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
            
            if (board[i][j] == '1') {
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
                }
            }

            /*
                    +---+  
                      3 | 
                +   .   +
                | 3     
                +---+   .
            */
            if (board[i][j] == '3' && board[i+1][j-1] == '3') {
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
            if (board[i][j] == '3' && board[i+1][j+1] == '3') {
                if (!assertDiff(now, i, j, i-1, j, cg) || 
                    !assertDiff(now, i, j, i, j-1, cg) || 
                    !assertDiff(now, i+1, j+1, i+1, j+2, cg) ||
                    !assertDiff(now, i+1, j+1, i+2, j+1, cg)) {
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
            if (board[i][j] == '1' && board[i+1][j-1] == '1') {
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
            if (board[i][j] == '1' && board[i+1][j+1] == '1') {
                if (isSame(now, i, j, i-1, j) && isSame(now, i, j, i, j-1)) {
                    if (!assertSame(now, i+1, j+1, i+1, j+2, cg) || !assertSame(now, i+1, j+1, i+2, j+1, cg))
                        return false;
                }
                if (isSame(now, i+1, j+1, i+1, j+2) && isSame(now, i+1, j+1, i+2, j+1)) {
                    if (!assertSame(now, i, j, i-1, j, cg) || !assertSame(now, i, j, i, j-1, cg))
                        return false;
                }
            }


            if (board[i][j] == '3') {
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
        }
    }

    return true;
}

void initalRules(Slither &now) {
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

    // 如果 0 出现在角落里，则它和周围两格必为 OUTER
    if (board[1][1] == '0') setStatus(now, 1, 1, OUTER), setStatus(now, 1, 2, OUTER),   setStatus(now, 2, 1, OUTER);
    if (board[1][m] == '0') setStatus(now, 1, m, OUTER), setStatus(now, 1, m-1, OUTER), setStatus(now, 2, m, OUTER);
    if (board[n][1] == '0') setStatus(now, n, 1, OUTER), setStatus(now, n-1, 1, OUTER), setStatus(now, n, 2, OUTER);
    if (board[n][m] == '0') setStatus(now, n, m, OUTER), setStatus(now, n-1, m, OUTER), setStatus(now, n, m-1, OUTER);

    // 如果 2 出现在角落里，则周围两格必为 INNER，它自己不一定
    if (board[1][1] == '0') setStatus(now, 1, 2, INNER),   setStatus(now, 2, 1, INNER);
    if (board[1][m] == '0') setStatus(now, 1, m-1, INNER), setStatus(now, 2, m, INNER);
    if (board[n][1] == '0') setStatus(now, n-1, 1, INNER), setStatus(now, n, 2, INNER);
    if (board[n][m] == '0') setStatus(now, n-1, m, INNER), setStatus(now, n, m-1, INNER);
}

bool solve(Slither now) {
    if (!applyRules(now)) return false;
    if (!checkHole(now)) return false;

    auto [i, j] = findFirst(now, UNKNOWN);
    if (i == -1) {
        if (isConnected(now) && checkNumber(now)) {
            finalAns = now;
            return true;
        } else {
            return false;
        }
    }

    CUR = INNER;
    if (solve(now)) return true;
    CUR = OUTER;
    if (solve(now)) return true;
    return false;
}

vector<string> Slitherlink(vector<string> _board){
    addBoundary(_board);
    auto slither = newSlither();
    initalRules(slither);
    if (solve(slither)) {
        auto ans = _board;
        FORCELL{
            ans[i-1][j-1] = (finalAns[i][j] == INNER) ? '*' : '.';
        }
        return ans;
    } else {
        cerr << "Slitherlink: no solution." << endl;
        return vector<string>();
    }
}