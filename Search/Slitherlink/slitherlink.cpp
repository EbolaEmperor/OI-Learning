#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#ifndef SLINK_BRANCH_MORE_DEPTH
#define SLINK_BRANCH_MORE_DEPTH 4
#endif
static constexpr int kBranchMoreDepth = SLINK_BRANCH_MORE_DEPTH;
#ifndef SLINK_BRANCH_MORE_DEPTH_SMALL
#define SLINK_BRANCH_MORE_DEPTH_SMALL 8
#endif
static constexpr int kBranchMoreDepthSmall = SLINK_BRANCH_MORE_DEPTH_SMALL;
#ifndef SLINK_CONNECTOR_DEPTH
#define SLINK_CONNECTOR_DEPTH 1000000
#endif
static constexpr int kConnectorDepth = SLINK_CONNECTOR_DEPTH;
#ifndef SLINK_CONNECTOR_MIN_SIZE
#define SLINK_CONNECTOR_MIN_SIZE 25
#endif
static constexpr int kConnectorMinSize = SLINK_CONNECTOR_MIN_SIZE;
#ifndef SLINK_CLUSTER_MIN_SIZE
#define SLINK_CLUSTER_MIN_SIZE 19
#endif
static constexpr int kClusterMinSize = SLINK_CLUSTER_MIN_SIZE;
#ifndef SLINK_INNER_CONNECTOR_MIN_ZEROS
#define SLINK_INNER_CONNECTOR_MIN_ZEROS 15
#endif
static constexpr int kInnerConnectorMinZeros = SLINK_INNER_CONNECTOR_MIN_ZEROS;
#ifndef SLINK_SCORE_ADJ
#define SLINK_SCORE_ADJ 0
#endif
#ifndef SLINK_SCORE_NUM_BASE
#define SLINK_SCORE_NUM_BASE 320
#endif
#ifndef SLINK_SCORE_NUM_UNK
#define SLINK_SCORE_NUM_UNK 40
#endif
#ifndef SLINK_SCORE_VERTEX_BASE
#define SLINK_SCORE_VERTEX_BASE 8
#endif
#ifndef SLINK_SCORE_VERTEX_UNK
#define SLINK_SCORE_VERTEX_UNK 1
#endif
#ifndef SLINK_LARGE_SCORE_MIN_SIZE
#define SLINK_LARGE_SCORE_MIN_SIZE 28
#endif
static constexpr int kLargeScoreMinSize = SLINK_LARGE_SCORE_MIN_SIZE;
#ifndef SLINK_LOOKAHEAD_TOP
#define SLINK_LOOKAHEAD_TOP 32
#endif
static constexpr int kLookaheadTop = SLINK_LOOKAHEAD_TOP;
#ifndef SLINK_LOOKAHEAD_TOP_LARGE
#define SLINK_LOOKAHEAD_TOP_LARGE 64
#endif
static constexpr int kLookaheadTopLarge = SLINK_LOOKAHEAD_TOP_LARGE;
static constexpr int kLookaheadStorage = kLookaheadTop > kLookaheadTopLarge ? kLookaheadTop : kLookaheadTopLarge;
#ifndef SLINK_LOOKAHEAD_MIN_SIZE
#define SLINK_LOOKAHEAD_MIN_SIZE 19
#endif
static constexpr int kLookaheadMinSize = SLINK_LOOKAHEAD_MIN_SIZE;
#ifndef SLINK_LOOKAHEAD_MAX_SIZE
#define SLINK_LOOKAHEAD_MAX_SIZE 28
#endif
static constexpr int kLookaheadMaxSize = SLINK_LOOKAHEAD_MAX_SIZE;
#ifndef SLINK_LOOKAHEAD_DEPTH
#define SLINK_LOOKAHEAD_DEPTH 1000000
#endif
static constexpr int kLookaheadDepth = SLINK_LOOKAHEAD_DEPTH;
#ifndef SLINK_FULL_TOP_DEPTH
#define SLINK_FULL_TOP_DEPTH 0
#endif
static constexpr int kFullTopDepth = SLINK_FULL_TOP_DEPTH;
#ifndef SLINK_LOOKAHEAD_TOP_DEEP
#define SLINK_LOOKAHEAD_TOP_DEEP 40
#endif
static constexpr int kLookaheadTopDeep = SLINK_LOOKAHEAD_TOP_DEEP;
#ifndef SLINK_RECT_CLUSTER_MAX_MASKS
#define SLINK_RECT_CLUSTER_MAX_MASKS 36
#endif
static constexpr size_t kRectClusterMaxMasks = SLINK_RECT_CLUSTER_MAX_MASKS;

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

struct ConstraintResult {
    uint8_t valid = 0;
    array<uint8_t, 5> force{};
};

struct NumberConstraint {
    array<size_t, 5> ids{};
    uint8_t lim = 0;
};

struct VertexConstraint {
    array<size_t, 4> ids{};
};

vector<string> board;
vector<cord> numberedCells;
vector<cord> vertexCells;
vector<NumberConstraint> numberConstraints;
vector<VertexConstraint> vertexConstraints;
int zeroClues = 0;
Slither finalAns;
vector<size_t> bfsQueue;
vector<uint32_t> connectedMark;
uint32_t connectedStamp = 0;
vector<int> dfsDisc;
vector<int> dfsLow;
vector<int> dfsSubCount;
vector<uint32_t> dfsSeen;
uint32_t dfsStamp = 0;
array<array<ConstraintResult, 243>, 5> numberConstraintTable;
array<ConstraintResult, 81> vertexConstraintTable;
bool constraintTablesReady = false;

struct LocalCluster {
    array<size_t, 16> ids{};
    array<cord, 8> clues{};
    int cnt = 0;
    int clueCnt = 0;
    bool valid = true;
    uint64_t allBits = 0;
    vector<uint64_t> masks;
    vector<uint64_t> outerMasks;
};

vector<LocalCluster> localClusters;

// ===== 工具函数 =====
static inline void buildConstraintTables();

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
    buildConstraintTables();
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

    numberedCells.clear();
    numberedCells.reserve((size_t)n * m);
    numberConstraints.clear();
    numberConstraints.reserve((size_t)n * m);
    zeroClues = 0;
    FORCELL {
        if (board[i][j] != '.') {
            numberedCells.emplace_back(i, j);
            numberConstraints.push_back(NumberConstraint{{
                ID(i, j),
                ID(i, j + 1),
                ID(i + 1, j),
                ID(i, j - 1),
                ID(i - 1, j)
            }, (uint8_t)(board[i][j] - '0')});
            zeroClues += board[i][j] == '0';
        }
    }

    vertexCells.clear();
    vertexCells.reserve((size_t)(n + 1) * (m + 1));
    vertexConstraints.clear();
    vertexConstraints.reserve((size_t)(n + 1) * (m + 1));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            vertexCells.emplace_back(i, j);
            vertexConstraints.push_back(VertexConstraint{{
                ID(i, j),
                ID(i, j + 1),
                ID(i + 1, j),
                ID(i + 1, j + 1)
            }});
        }
}

static inline void buildConstraintTables() {
    if (constraintTablesReady) return;

    for (int lim = 0; lim <= 4; ++lim) {
        for (int code = 0; code < 243; ++code) {
            int cur[5];
            int tmp = code;
            for (int p = 0; p < 5; ++p) {
                cur[p] = tmp % 3;
                tmp /= 3;
            }

            int possible[5] = {0, 0, 0, 0, 0};
            bool any = false;
            for (int mask = 0; mask < 32; ++mask) {
                int val[5];
                bool ok = true;
                for (int p = 0; p < 5; ++p) {
                    val[p] = (mask & (1 << p)) ? INNER : OUTER;
                    if (cur[p] != UNKNOWN && cur[p] != val[p]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) continue;

                int cnt = 0;
                for (int p = 1; p < 5; ++p)
                    cnt += (val[p] != val[0]);
                if (cnt != lim) continue;

                any = true;
                for (int p = 0; p < 5; ++p)
                    possible[p] |= (val[p] == INNER ? 1 : 2);
            }

            ConstraintResult &res = numberConstraintTable[lim][code];
            res.valid = any;
            for (int p = 0; p < 5; ++p) {
                if (cur[p] == UNKNOWN && (possible[p] == 1 || possible[p] == 2))
                    res.force[p] = (uint8_t)(possible[p] == 1 ? INNER : OUTER);
                else
                    res.force[p] = UNKNOWN;
            }
        }
    }

    for (int code = 0; code < 81; ++code) {
        int cur[4];
        int tmp = code;
        for (int p = 0; p < 4; ++p) {
            cur[p] = tmp % 3;
            tmp /= 3;
        }

        int possible[4] = {0, 0, 0, 0};
        bool any = false;
        for (int mask = 0; mask < 16; ++mask) {
            int val[4];
            bool ok = true;
            for (int p = 0; p < 4; ++p) {
                val[p] = (mask & (1 << p)) ? INNER : OUTER;
                if (cur[p] != UNKNOWN && cur[p] != val[p]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            int deg = 0;
            deg += (val[0] != val[1]);
            deg += (val[1] != val[3]);
            deg += (val[2] != val[3]);
            deg += (val[0] != val[2]);
            if (deg != 0 && deg != 2) continue;

            any = true;
            for (int p = 0; p < 4; ++p)
                possible[p] |= (val[p] == INNER ? 1 : 2);
        }

        ConstraintResult &res = vertexConstraintTable[code];
        res.valid = any;
        for (int p = 0; p < 4; ++p) {
            if (cur[p] == UNKNOWN && (possible[p] == 1 || possible[p] == 2))
                res.force[p] = (uint8_t)(possible[p] == 1 ? INNER : OUTER);
            else
                res.force[p] = UNKNOWN;
        }
        res.force[4] = UNKNOWN;
    }

    constraintTablesReady = true;
}

// 寻找 now 里面第一个为 sta 的状态
static inline cord findFirst(const Slither &now, Status sta) {
    FORCELL{
        if (now[ID(i,j)] == sta)
            return cord(i, j);
    }
    return cord(-1,-1);
}

static inline int clusterIndexOf(const LocalCluster &cluster, size_t id) {
    for (int p = 0; p < cluster.cnt; ++p)
        if (cluster.ids[p] == id) return p;
    return -1;
}

static inline void addClusterCell(LocalCluster &cluster, int i, int j) {
    if (!cluster.valid) return;
    if (!INBOARD(i, j)) return;
    size_t id = ID(i, j);
    if (clusterIndexOf(cluster, id) != -1) return;
    if (cluster.cnt == (int)cluster.ids.size()) {
        cluster.valid = false;
        return;
    }
    cluster.ids[cluster.cnt++] = id;
}

static inline int clusterMaskValue(const LocalCluster &cluster, uint64_t mask, int i, int j, bool &known) {
    if (!INBOARD(i, j)) return 0;
    int idx = clusterIndexOf(cluster, ID(i, j));
    if (idx == -1) {
        known = false;
        return 0;
    }
    return (mask >> idx) & 1;
}

static inline bool clusterMaskNumberOk(const LocalCluster &cluster, uint64_t mask, int i, int j) {
    bool known = true;
    int center = clusterMaskValue(cluster, mask, i, j, known);
    if (!known) return false;
    int cnt = 0;
    for (int k = 0; k < 4; ++k) {
        bool adjKnown = true;
        int adj = clusterMaskValue(cluster, mask, i + adj4[k][0], j + adj4[k][1], adjKnown);
        if (!adjKnown) return false;
        cnt += center != adj;
    }
    return cnt == board[i][j] - '0';
}

static inline bool clusterMaskVertexOk(const LocalCluster &cluster, uint64_t mask, int i, int j) {
    bool known = true;
    int a = clusterMaskValue(cluster, mask, i, j, known);
    if (!known) return true;
    int b = clusterMaskValue(cluster, mask, i, j + 1, known);
    if (!known) return true;
    int c = clusterMaskValue(cluster, mask, i + 1, j, known);
    if (!known) return true;
    int d = clusterMaskValue(cluster, mask, i + 1, j + 1, known);
    if (!known) return true;

    int deg = 0;
    deg += a != b;
    deg += b != d;
    deg += c != d;
    deg += a != c;
    return deg == 0 || deg == 2;
}

static inline void finishLocalCluster(LocalCluster &cluster) {
    if (!cluster.valid) return;
    const uint64_t totalMasks = 1ULL << cluster.cnt;
    cluster.allBits = totalMasks - 1;
    int minI = n + 1, maxI = 0, minJ = m + 1, maxJ = 0;
    for (int p = 0; p < cluster.cnt; ++p) {
        int x = (int)(cluster.ids[p] / (size_t)(m + 2));
        int y = (int)(cluster.ids[p] % (size_t)(m + 2));
        minI = min(minI, x);
        maxI = max(maxI, x);
        minJ = min(minJ, y);
        maxJ = max(maxJ, y);
    }

    for (uint64_t mask = 0; mask < totalMasks; ++mask) {
        bool clueOk = true;
        for (int p = 0; p < cluster.clueCnt; ++p) {
            auto [i, j] = cluster.clues[p];
            if (!clusterMaskNumberOk(cluster, mask, i, j)) {
                clueOk = false;
                break;
            }
        }
        if (!clueOk) continue;

        bool ok = true;
        for (int i = max(0, minI - 1); ok && i <= min(n, maxI); ++i) {
            for (int j = max(0, minJ - 1); j <= min(m, maxJ); ++j) {
                if (!clusterMaskVertexOk(cluster, mask, i, j)) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            cluster.masks.push_back(mask);
            cluster.outerMasks.push_back((~mask) & cluster.allBits);
        }
    }
}

static inline void buildLocalClusters() {
    localClusters.clear();
    if (n < kClusterMinSize || m < kClusterMinSize ||
        n > kLookaheadMaxSize || m > kLookaheadMaxSize) {
        return;
    }
    localClusters.reserve(numberedCells.size() * 2);
    for (auto [i, j] : numberedCells) {
        const int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int dir = 0; dir < 4; ++dir) {
            int di = dirs[dir][0], dj = dirs[dir][1];
            int x = i + di, y = j + dj;
            if (!INBOARD(x, y) || board[x][y] == '.') continue;

            LocalCluster cluster;
            cluster.clues[cluster.clueCnt++] = cord(i, j);
            cluster.clues[cluster.clueCnt++] = cord(x, y);
            for (int t = 0; t < cluster.clueCnt; ++t) {
                auto [ci, cj] = cluster.clues[t];
                addClusterCell(cluster, ci, cj);
                for (int k = 0; k < 4; ++k)
                    addClusterCell(cluster, ci + adj4[k][0], cj + adj4[k][1]);
            }
            finishLocalCluster(cluster);
            if (!cluster.masks.empty()) localClusters.push_back(std::move(cluster));
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            LocalCluster cluster;
            for (int di = 0; di <= 1; ++di) {
                for (int dj = 0; dj <= 1; ++dj) {
                    int x = i + di, y = j + dj;
                    if (board[x][y] != '.') cluster.clues[cluster.clueCnt++] = cord(x, y);
                }
            }
            if (cluster.clueCnt < 3) continue;
            for (int t = 0; t < cluster.clueCnt; ++t) {
                auto [ci, cj] = cluster.clues[t];
                addClusterCell(cluster, ci, cj);
                for (int k = 0; k < 4; ++k)
                    addClusterCell(cluster, ci + adj4[k][0], cj + adj4[k][1]);
            }
            finishLocalCluster(cluster);
            if (!cluster.masks.empty()) localClusters.push_back(std::move(cluster));
        }
    }

    const int rects[2][2] = {{2, 3}, {3, 2}};
    for (auto [height, width] : rects) {
        for (int i = 1; i + height - 1 <= n; ++i) {
            for (int j = 1; j + width - 1 <= m; ++j) {
                LocalCluster cluster;
                for (int di = 0; di < height; ++di) {
                    for (int dj = 0; dj < width; ++dj) {
                        int x = i + di, y = j + dj;
                        if (board[x][y] != '.') cluster.clues[cluster.clueCnt++] = cord(x, y);
                    }
                }
                if (cluster.clueCnt < 4) continue;
                for (int t = 0; t < cluster.clueCnt; ++t) {
                    auto [ci, cj] = cluster.clues[t];
                    addClusterCell(cluster, ci, cj);
                    for (int k = 0; k < 4; ++k)
                        addClusterCell(cluster, ci + adj4[k][0], cj + adj4[k][1]);
                }
                finishLocalCluster(cluster);
                if (cluster.valid && !cluster.masks.empty() && cluster.masks.size() <= kRectClusterMaxMasks)
                    localClusters.push_back(std::move(cluster));
            }
        }
    }
}

// 检查数字周围是否有正确数量的线
static inline bool checkNumber(const Slither &now) {
    for (auto [i, j] : numberedCells) {
        char c = board[i][j];
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

    const size_t W = (size_t)m + 2;
    const size_t total = ((size_t)n + 2) * W;
    if (connectedMark.size() < total) connectedMark.assign(total, 0);
    if (++connectedStamp == 0) {
        fill(connectedMark.begin(), connectedMark.end(), 0);
        connectedStamp = 1;
    }
    if (bfsQueue.capacity() < total) bfsQueue.reserve(total);

    bfsQueue.clear();
    size_t head = 0;
    size_t start = ID(i0, j0);
    bfsQueue.push_back(start);
    connectedMark[start] = connectedStamp;

    while (head < bfsQueue.size()) {
        size_t id = bfsQueue[head++];
        int i = (int)(id / W), j = (int)(id % W);

        if (j < m) {
            size_t nxt = id + 1;
            if (connectedMark[nxt] != connectedStamp && (now[nxt] == INNER || now[nxt] == UNKNOWN)) {
                connectedMark[nxt] = connectedStamp;
                bfsQueue.push_back(nxt);
            }
        }
        if (i < n) {
            size_t nxt = id + W;
            if (connectedMark[nxt] != connectedStamp && (now[nxt] == INNER || now[nxt] == UNKNOWN)) {
                connectedMark[nxt] = connectedStamp;
                bfsQueue.push_back(nxt);
            }
        }
        if (j > 1) {
            size_t nxt = id - 1;
            if (connectedMark[nxt] != connectedStamp && (now[nxt] == INNER || now[nxt] == UNKNOWN)) {
                connectedMark[nxt] = connectedStamp;
                bfsQueue.push_back(nxt);
            }
        }
        if (i > 1) {
            size_t nxt = id - W;
            if (connectedMark[nxt] != connectedStamp && (now[nxt] == INNER || now[nxt] == UNKNOWN)) {
                connectedMark[nxt] = connectedStamp;
                bfsQueue.push_back(nxt);
            }
        }
    }

    FORCELL {
        size_t id = ID(i, j);
        if (now[id] == INNER && connectedMark[id] != connectedStamp) return false;
    }
    return true;
}

// 检查是否有 OUTER 被 INNER 包起来形成一个洞
// 如果有 UNKNOWN 被 INNER 包起来，那就把它设为 INNER
static inline bool checkHole(Slither &now, bool *changed = nullptr) {
    if (changed) *changed = false;
    const size_t W = (size_t)m + 2;
    const size_t total = ((size_t)n + 2) * W;
    if (bfsQueue.capacity() < total) bfsQueue.reserve(total);
    bfsQueue.clear();
    size_t head = 0;
    bfsQueue.push_back(0);
    now[0] = OUTER_BFS;

    while(head < bfsQueue.size()) {
        size_t id = bfsQueue[head++];
        int i = (int)(id / W), j = (int)(id % W);

        auto pushReachable = [&](size_t nxt) {
            Status &adj = now[nxt];
            if (adj == UNKNOWN) {
                adj = UNKNOWN_BFS;
                bfsQueue.push_back(nxt);
            } else if (adj == OUTER) {
                adj = OUTER_BFS;
                bfsQueue.push_back(nxt);
            }
        };

        if (j < m + 1) pushReachable(id + 1);
        if (i < n + 1) pushReachable(id + W);
        if (j > 0) pushReachable(id - 1);
        if (i > 0) pushReachable(id - W);
    }

    for (size_t id = 0; id < total; ++id) {
        Status &cur = now[id];
        if (cur == OUTER) return false;
        else if (cur == UNKNOWN) {
            cur = INNER;
            if (changed) *changed = true;
        }
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

static inline bool forceStatus(Slither &now, int i, int j, Status sta, bool &cg) {
    Status &cur = now[ID(i,j)];
    if (cur == UNKNOWN) {
        cur = sta;
        cg = true;
        return true;
    }
    return cur == sta;
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

static inline bool applyNumberConstraint(Slither &now, const NumberConstraint &constraint, bool &cg) {
    const auto &ids = constraint.ids;
    int code = 0;
    int mul = 1;
    for (int p = 0; p < 5; ++p) {
        code += (int)now[ids[p]] * mul;
        mul *= 3;
    }
    const ConstraintResult &res = numberConstraintTable[constraint.lim][code];
    if (!res.valid) return false;
    for (int p = 0; p < 5; ++p) {
        if (res.force[p] != UNKNOWN) {
            now[ids[p]] = (Status)res.force[p];
            cg = true;
        }
    }
    return true;
}

static inline bool applyVertexConstraint(Slither &now, const VertexConstraint &constraint, bool &cg) {
    const auto &ids = constraint.ids;
    int code = 0;
    int mul = 1;
    for (int p = 0; p < 4; ++p) {
        code += (int)now[ids[p]] * mul;
        mul *= 3;
    }
    const ConstraintResult &res = vertexConstraintTable[code];
    if (!res.valid) return false;
    for (int p = 0; p < 4; ++p) {
        if (res.force[p] != UNKNOWN) {
            now[ids[p]] = (Status)res.force[p];
            cg = true;
        }
    }
    return true;
}

static inline bool applyLocalClusterConstraint(Slither &now, const LocalCluster &cluster, bool &cg) {
    uint64_t knownInner = 0;
    uint64_t knownOuter = 0;
    for (int p = 0; p < cluster.cnt; ++p) {
        Status cur = now[cluster.ids[p]];
        if (cur == INNER) knownInner |= 1ULL << p;
        else if (cur == OUTER) knownOuter |= 1ULL << p;
    }

    uint64_t possibleInner = 0;
    uint64_t possibleOuter = 0;
    bool any = false;
    const size_t maskCount = cluster.masks.size();
    for (size_t idx = 0; idx < maskCount; ++idx) {
        uint64_t mask = cluster.masks[idx];
        uint64_t outerMask = cluster.outerMasks[idx];
        if ((mask & knownOuter) != 0) continue;
        if ((outerMask & knownInner) != 0) continue;
        any = true;
        possibleInner |= mask;
        possibleOuter |= outerMask;
    }
    if (!any) return false;

    for (int p = 0; p < cluster.cnt; ++p) {
        Status &cur = now[cluster.ids[p]];
        if (cur != UNKNOWN) continue;
        bool canInner = (possibleInner >> p) & 1;
        bool canOuter = (possibleOuter >> p) & 1;
        if (canInner == canOuter) continue;
        cur = canInner ? INNER : OUTER;
        cg = true;
    }
    return true;
}

static inline bool applyRules(Slither &now) {
    bool cg = true;
    const bool eagerGeneric = n <= 16 && m <= 16;
    bool runGeneric = eagerGeneric;
    auto [i0, j0] = findFirst(now, UNKNOWN);
    while(cg) {
        cg = false;
        if (runGeneric || eagerGeneric) {
            for (const auto &constraint : numberConstraints) {
                if (!applyNumberConstraint(now, constraint, cg)) return false;
            }
            for (const auto &constraint : vertexConstraints) {
                if (!applyVertexConstraint(now, constraint, cg)) return false;
            }
            if (n >= kClusterMinSize && m >= kClusterMinSize &&
                n <= kLookaheadMaxSize && m <= kLookaheadMaxSize) {
                for (const auto &cluster : localClusters) {
                    if (!applyLocalClusterConstraint(now, cluster, cg)) return false;
                }
            }
            if (cg && !eagerGeneric) {
                runGeneric = eagerGeneric;
                continue;
            }
        }
        for (int i = max(1, i0-1); i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = board[i][j];

            // 数字 0 必须和他周围四个格子在同一个 region 里
            if (c == '0')
                FORADJ4 if(!assertSame(now, i, j, ADJX, ADJY, cg))
                    return false;

            if (now[ID(i,j)] != UNKNOWN && c != '.' && c != '0') {
                // 检查有数字的位置，如果线连满了，就把其余的线设为不连接
                int cnt = 0, lim = c - '0';
                FORADJ4 {
                    if (now[ID(ADJX,ADJY)] != UNKNOWN && now[ID(i,j)] != now[ID(ADJX,ADJY)]) ++cnt;
                }
                if (cnt > lim) return false;
                if (cnt == lim) {
                    FORADJ4 {
                        if (now[ID(ADJX,ADJY)] == UNKNOWN)
                            if (!forceStatus(now, ADJX, ADJY, now[ID(i,j)], cg)) return false;
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
                            if (!forceStatus(now, ADJX, ADJY, diff(now[ID(i,j)]), cg)) return false;
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

                    //         +     +     +     +     +                    +     +     +     +     +  
                    //                  1     1                                      1  x  1           
                    //         +     +     +     +     +         =>         +     +     +     +     +  
                    //                        0                                            0           
                    //         +     +     +     +     +                    +     +     +     +     +
                    if (board[ADJ8X(k)][ADJ8Y(k)] == '1' && (board[ADJ8X(k+1)][ADJ8Y(k+1)] == '0' || board[ADJ8X(k+7)][ADJ8Y(k+7)] == '0')) {
                        if (!assertSame(now, i, j, ADJ8(k), cg)) return false;
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
            //                        3                        =>               x     x  3                 
            //         +     +  -  +     +     +     +                    +     +  -  +     +     +     + 
            if (c == '3') {
                for (int k = 0; k < 8; k += 2) 
                    if (isDiff(now, ADJ8(k), ADJ8(k+1)) && isDiff(now, ADJ8(k), ADJ8(k+7))) {
                        if (!assertSame(now, i, j, ADJ8(k), cg) || 
                            !assertSame(now, ADJ8(k), i + 2*adj8[k][0], j + 2*adj8[k][1], cg))
                            return false;
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

            //         +     +     +     +     +     +                    +     +     +  -  +     +     +  
            //                        2                                                  2                 
            //         +     +  -  +     +  -  +     +                    +     +  -  +     +  -  +     +  
            //                        2                        =>                        2                 
            //         +     +     +     +     +     +                    +     +     +  -  +     +     +  
            if (c == '2' && board[i+1][j] == '2') {
                if (isDiff(now, i, j-1, i+1, j-1) && isDiff(now, i, j+1, i+1, j+1)) {
                    if (!assertDiff(now, i, j, i-1, j, cg) || !assertDiff(now, i+1, j, i+2, j, cg))
                        return false;
                }
            }
            if (c == '2' && board[i][j+1] == '2') {
                if (isDiff(now, i-1, j, i-1, j+1) && isDiff(now, i+1, j, i+1, j+1)) {
                    if (!assertDiff(now, i, j, i, j-1, cg) || !assertDiff(now, i, j+1, i, j+2, cg))
                        return false;
                }
            }

            //         +     +     +     +     +     +                    +     +     +  x  +     +     +  
            //                        1                                                  1  x              
            //         +     +  x  +     +     +     +                    +     +  x  +     +     +     +  
            //                        2                                               |  2                 
            //         +     +     +     +     +     +         =>         +     +     +     +     +     +  
            //                           |                                                  |              
            //         +     +     +     +     +     +                    +     +     +     +     +     +  
            if (c == '2') {
                for (int k = 0; k < 8; k += 2) {
                    if (board[ADJ8X(k+6)][ADJ8Y(k+6)] == '1' && isDiff(now, ADJ8(k+1), ADJ8(k+2)) && isSame(now, ADJ8(k+4), ADJ8(k+5))) {
                        if (!assertDiff(now, i, j, ADJ8(k+4), cg) 
                         || !assertSame(now, ADJ8(k+6), i + 2*adj8[k+6][0], j + 2*adj8[k+6][1], cg)
                         || !assertSame(now, ADJ8(k+6), ADJ8(k+7), cg))
                         return false;
                    }
                }
            }

            /*
                        +---+
                          3 |
                    .   .   +
                      2   
                +   .   .
                | 3     
                +---+   .
            */
            if (c == '3' && board[i+1][j-1] == '2' && board[i+2][j-2] == '3') {
                if (!assertDiff(now, i, j, i-1, j, cg) || 
                    !assertDiff(now, i, j, i, j+1, cg) || 
                    !assertDiff(now, i+2, j-2, i+2, j-3, cg) ||
                    !assertDiff(now, i+2, j-2, i+3, j-2, cg)) {
                        return false;
                }
            }

            /*
                +---+   .   .
                | 3       
                +   .   .   .
                      2  
                .   .   .   +
                          3 |
                .   .   +---+
            */
            if (c == '3' && board[i+1][j+1] == '2' && board[i+2][j+2] == '3') {
                if (!assertDiff(now, i, j, i-1, j, cg) || 
                    !assertDiff(now, i, j, i, j-1, cg) || 
                    !assertDiff(now, i+2, j+2, i+2, j+3, cg) ||
                    !assertDiff(now, i+2, j+2, i+3, j+2, cg)) {
                        return false;
                }
            }
        }
        if (!cg && !runGeneric && !eagerGeneric) {
            runGeneric = true;
            cg = true;
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

    //  #############
    //  +   +   +   #
    //    1   1(out)# 
    //  +---+   +   #
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

    //  ###########
    //  +---+   + #
    //  | 3   2   #
    //  +   +   + #
    if (board[1][1] == '2' && board[1][2] == '3') setStatus(now, 1, 3, OUTER);
    if (board[1][1] == '2' && board[2][1] == '3') setStatus(now, 3, 1, OUTER);
    if (board[1][m] == '2' && board[1][m-1] == '3') setStatus(now, 1, m-2, OUTER);
    if (board[1][m] == '2' && board[2][m] == '3') setStatus(now, 3, m, OUTER);
    if (board[n][1] == '2' && board[n][2] == '3') setStatus(now, n, 3, OUTER);
    if (board[n][1] == '2' && board[n-1][1] == '3') setStatus(now, n-2, 1, OUTER);
    if (board[n][m] == '2' && board[n-1][m] == '3') setStatus(now, n-2, m, OUTER);
    if (board[n][m] == '2' && board[n][m-1] == '3') setStatus(now, n, m-2, OUTER);

    //  ###########
    //  +---+   + #
    //    3 | 1   #
    //  +   +   + #
    if (board[1][1] == '1' && board[1][2] == '3') setStatus(now, 1, 2, INNER);
    if (board[1][1] == '1' && board[2][1] == '3') setStatus(now, 2, 1, INNER);
    if (board[1][m] == '1' && board[1][m-1] == '3') setStatus(now, 1, m-1, INNER);
    if (board[1][m] == '1' && board[2][m] == '3') setStatus(now, 2, m, INNER);
    if (board[n][1] == '1' && board[n][2] == '3') setStatus(now, n, 2, INNER);
    if (board[n][1] == '1' && board[n-1][1] == '3') setStatus(now, n-1, 1, INNER);
    if (board[n][m] == '1' && board[n-1][m] == '3') setStatus(now, n-1, m, INNER);
    if (board[n][m] == '1' && board[n][m-1] == '3') setStatus(now, n, m-1, INNER);
}

static inline bool forceConnectivityConnectors(Slither &now, bool &changed);

static inline void prepareDfsArrays(size_t total) {
    if (dfsDisc.size() < total) {
        dfsDisc.resize(total);
        dfsLow.resize(total);
        dfsSubCount.resize(total);
        dfsSeen.resize(total);
    }
    if (++dfsStamp == 0) {
        fill(dfsSeen.begin(), dfsSeen.end(), 0);
        dfsStamp = 1;
    }
}

static inline bool normalize(Slither &now, int depth = 0) {
    while (true) {
        if (!applyRules(now)) return false;
        bool holeChanged = false;
        if (!checkHole(now, &holeChanged)) return false;
        if (!isConnected(now)) return false;
        bool connectorChanged = false;
        if (depth <= kConnectorDepth && !forceConnectivityConnectors(now, connectorChanged)) return false;
        if (!holeChanged && !connectorChanged) return true;
    }
}

static void dfsInnerConnector(Slither &now, size_t u, size_t parent, int totalInner, bool &changed, int &timer) {
    const size_t W = (size_t)m + 2;
    dfsSeen[u] = dfsStamp;
    dfsDisc[u] = dfsLow[u] = ++timer;
    dfsSubCount[u] = (now[u] == INNER);
    int i = (int)(u / W), j = (int)(u % W);

    auto handleChild = [&](size_t v) {
        if (now[v] == OUTER) return;
        if (dfsSeen[v] != dfsStamp) {
            dfsInnerConnector(now, v, u, totalInner, changed, timer);
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
            dfsSubCount[u] += dfsSubCount[v];
            if (now[u] == UNKNOWN && dfsLow[v] >= dfsDisc[u] &&
                dfsSubCount[v] > 0 && totalInner - dfsSubCount[v] > 0) {
                now[u] = INNER;
                changed = true;
            }
        } else if (v != parent) {
            dfsLow[u] = min(dfsLow[u], dfsDisc[v]);
        }
    };

    if (j < m) handleChild(u + 1);
    if (i < n) handleChild(u + W);
    if (j > 1) handleChild(u - 1);
    if (i > 1) handleChild(u - W);
}

static inline bool forceInnerConnectors(Slither &now, bool &changed) {
    int totalInner = 0;
    size_t start = (size_t)-1;
    FORCELL {
        size_t id = ID(i, j);
        if (now[id] == INNER) {
            ++totalInner;
            start = id;
        }
    }
    if (totalInner <= 1) return true;

    const size_t W = (size_t)m + 2;
    const size_t total = ((size_t)n + 2) * W;
    prepareDfsArrays(total);
    int timer = 0;

    dfsInnerConnector(now, start, (size_t)-1, totalInner, changed, timer);
    return true;
}

static void dfsOuterConnector(Slither &now, size_t u, size_t parent, bool &changed, int &timer) {
    const size_t W = (size_t)m + 2;
    dfsSeen[u] = dfsStamp;
    dfsDisc[u] = dfsLow[u] = ++timer;
    int i = (int)(u / W), j = (int)(u % W);
    dfsSubCount[u] = (i >= 1 && i <= n && j >= 1 && j <= m && now[u] == OUTER);

    auto handleChild = [&](size_t v) {
        if (now[v] == INNER) return;
        if (dfsSeen[v] != dfsStamp) {
            dfsOuterConnector(now, v, u, changed, timer);
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
            dfsSubCount[u] += dfsSubCount[v];
            if (now[u] == UNKNOWN && dfsLow[v] >= dfsDisc[u] && dfsSubCount[v] > 0) {
                now[u] = OUTER;
                changed = true;
            }
        } else if (v != parent) {
            dfsLow[u] = min(dfsLow[u], dfsDisc[v]);
        }
    };

    if (j < m + 1) handleChild(u + 1);
    if (i < n + 1) handleChild(u + W);
    if (j > 0) handleChild(u - 1);
    if (i > 0) handleChild(u - W);
}

static inline bool forceOuterConnectors(Slither &now, bool &changed) {
    int totalBoardOuter = 0;
    FORCELL {
        totalBoardOuter += now[ID(i, j)] == OUTER;
    }
    if (totalBoardOuter == 0) return true;

    const size_t W = (size_t)m + 2;
    const size_t total = ((size_t)n + 2) * W;
    prepareDfsArrays(total);
    int timer = 0;

    dfsOuterConnector(now, 0, (size_t)-1, changed, timer);
    return true;
}

static inline bool forceConnectivityConnectors(Slither &now, bool &changed) {
    if (n < kConnectorMinSize && m < kConnectorMinSize) return true;
    if (zeroClues >= kInnerConnectorMinZeros && !forceInnerConnectors(now, changed)) return false;
    return forceOuterConnectors(now, changed);
}

static inline int countUnknown(const Slither &now) {
    int ret = 0;
    FORCELL {
        ret += now[ID(i,j)] == UNKNOWN;
    }
    return ret;
}

struct BranchCandidate {
    Slither state;
    int unknownCount;
};

struct CellCandidate {
    int i;
    int j;
    int score;
};

struct BranchChoice {
    int i = -1;
    int j = -1;
    int cnt = -1;
    int score = -1;
    BranchCandidate cand[2];
};

static inline int localConstraintScore(const Slither &now, int i, int j) {
    const bool largeBoardScore = n >= kLargeScoreMinSize || m >= kLargeScoreMinSize;
    const int adjScore = largeBoardScore ? SLINK_SCORE_ADJ : 6;
    const int numBase = largeBoardScore ? SLINK_SCORE_NUM_BASE : 80;
    const int numUnknownPenalty = largeBoardScore ? SLINK_SCORE_NUM_UNK : 10;
    const int vertexBase = largeBoardScore ? SLINK_SCORE_VERTEX_BASE : 24;
    const int vertexUnknownPenalty = largeBoardScore ? SLINK_SCORE_VERTEX_UNK : 4;
    int score = 0;

    FORADJ4 {
        if (now[ID(ADJX, ADJY)] != UNKNOWN) score += adjScore;
    }

    const int di[5] = {0, 0, 1, 0, -1};
    const int dj[5] = {0, 1, 0, -1, 0};
    for (int t = 0; t < 5; ++t) {
        int x = i + di[t], y = j + dj[t];
        if (!INBOARD(x, y) || board[x][y] == '.') continue;
        int unk = 0;
        if (now[ID(x, y)] == UNKNOWN) ++unk;
        for (int k = 0; k < 4; ++k)
            unk += now[ID(x + adj4[k][0], y + adj4[k][1])] == UNKNOWN;
        score += numBase - numUnknownPenalty * unk;
    }

    for (int x = i - 1; x <= i; ++x) {
        for (int y = j - 1; y <= j; ++y) {
            if (x < 0 || x > n || y < 0 || y > m) continue;
            int unk = 0;
            unk += now[ID(x, y)] == UNKNOWN;
            unk += now[ID(x, y + 1)] == UNKNOWN;
            unk += now[ID(x + 1, y)] == UNKNOWN;
            unk += now[ID(x + 1, y + 1)] == UNKNOWN;
            score += vertexBase - vertexUnknownPenalty * unk;
        }
    }

    return score;
}

static inline cord chooseBranchCell(const Slither &now) {
    int bestScore = -1;
    cord best(-1, -1);
    FORCELL {
        if (now[ID(i,j)] != UNKNOWN) continue;
        int score = localConstraintScore(now, i, j);
        if (score > bestScore) {
            bestScore = score;
            best = cord(i, j);
        }
    }
    return best;
}

static inline int activeLookaheadTop(int depth) {
    if (n < kLookaheadMinSize || m < kLookaheadMinSize ||
        n > kLookaheadMaxSize || m > kLookaheadMaxSize) {
        return 0;
    }
    if (n * m < 26 * 26) return kLookaheadTop;
    return depth <= kFullTopDepth ? kLookaheadTopLarge : kLookaheadTopDeep;
}

static inline bool shouldUseLookahead(int depth) {
    return depth <= kLookaheadDepth && activeLookaheadTop(depth) > 0;
}

static inline void insertTopCandidate(CellCandidate top[], int &cnt, int limit, const CellCandidate &cand) {
    int pos = cnt;
    if (pos < limit) {
        top[cnt++] = cand;
    } else if (cand.score > top[cnt - 1].score) {
        pos = cnt - 1;
        top[pos] = cand;
    } else {
        return;
    }
    while (pos > 0 && top[pos].score > top[pos - 1].score) {
        swap(top[pos], top[pos - 1]);
        --pos;
    }
}

static inline void orderBranchCandidates(BranchCandidate cand[2], int cnt, int depth) {
    if (cnt != 2) return;
    const int branchMoreDepth = (n < 28 && m < 28) ? kBranchMoreDepthSmall : kBranchMoreDepth;
    if (depth < branchMoreDepth) {
        if (cand[1].unknownCount > cand[0].unknownCount)
            swap(cand[0], cand[1]);
    } else if (cand[1].unknownCount < cand[0].unknownCount) {
        swap(cand[0], cand[1]);
    }
}

static inline int buildBranchCandidates(const Slither &now, int i, int j, int depth, BranchCandidate cand[2]) {
    int cnt = 0;
    for (Status sta : {INNER, OUTER}) {
        Slither nxt = now;
        nxt[ID(i,j)] = sta;
        if (normalize(nxt, depth)) {
            cand[cnt++] = BranchCandidate{std::move(nxt), 0};
            cand[cnt - 1].unknownCount = countUnknown(cand[cnt - 1].state);
        }
    }
    return cnt;
}

static inline bool betterLookaheadChoice(const BranchChoice &lhs, const BranchChoice &rhs) {
    if (rhs.cnt == -1) return true;
    if (lhs.cnt != rhs.cnt) return lhs.cnt < rhs.cnt;

    int lhsSum = 0, rhsSum = 0;
    for (int t = 0; t < lhs.cnt; ++t) {
        int unk = lhs.cand[t].unknownCount;
        lhsSum += unk;
    }
    for (int t = 0; t < rhs.cnt; ++t) {
        int unk = rhs.cand[t].unknownCount;
        rhsSum += unk;
    }

    int lhsBest = lhs.cnt == 0 ? -1 : lhs.cand[0].unknownCount;
    int rhsBest = rhs.cnt == 0 ? -1 : rhs.cand[0].unknownCount;

    if (lhsSum != rhsSum) return lhsSum < rhsSum;
    if (lhsBest != rhsBest) return lhsBest < rhsBest;
    return lhs.score > rhs.score;
}

static inline BranchChoice chooseBranch(Slither &now, int depth) {
    BranchChoice choice;
    if (!shouldUseLookahead(depth)) {
        auto [i, j] = chooseBranchCell(now);
        choice.i = i;
        choice.j = j;
        return choice;
    }

    CellCandidate top[kLookaheadStorage > 0 ? kLookaheadStorage : 1];
    int topCnt = 0;
    int topLimit = activeLookaheadTop(depth);
    FORCELL {
        if (now[ID(i,j)] != UNKNOWN) continue;
        insertTopCandidate(top, topCnt, topLimit, CellCandidate{i, j, localConstraintScore(now, i, j)});
    }
    if (topCnt == 0) return choice;

    for (int t = 0; t < topCnt; ++t) {
        BranchChoice cur;
        cur.i = top[t].i;
        cur.j = top[t].j;
        cur.score = top[t].score;
        cur.cnt = buildBranchCandidates(now, cur.i, cur.j, depth + 1, cur.cand);
        orderBranchCandidates(cur.cand, cur.cnt, depth);
        if (betterLookaheadChoice(cur, choice)) {
            choice = std::move(cur);
            if (choice.cnt <= 1) break;
        }
    }
    return choice;
}

static bool solve(Slither now, bool normalized = false, int depth = 0) {
    if (!normalized && !normalize(now, depth)) return false;

    BranchChoice choice = chooseBranch(now, depth);
    if (choice.i == -1) {
        if (checkNumber(now)) {
            finalAns = std::move(now);
            return true;
        } else {
            return false;
        }
    }

    if (choice.cnt == -1) {
        choice.cnt = buildBranchCandidates(now, choice.i, choice.j, depth + 1, choice.cand);
        orderBranchCandidates(choice.cand, choice.cnt, depth);
    }
    for (int t = 0; t < choice.cnt; ++t)
        if (solve(std::move(choice.cand[t].state), true, depth + 1)) return true;
    return false;
}

// === 输出字符画 ===
static void print_solution_ascii(const vector<string>& puzzle, const Slither& solved) {
    int n = (int)puzzle.size();
    int m = (int)puzzle[0].size();
    auto is_diff_region = [](Status a, Status b) { return a != b; };

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
    buildLocalClusters();
    auto slither = newSlither();
    initalRules(slither);
    finalAns.clear();
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


int count_sol = 0;

static void countSol(Slither now) {
    if (!normalize(now)) return;
    auto [i, j] = chooseBranchCell(now);
    if (i == -1) {
        count_sol += checkNumber(now);
        return;
    }
    CUR = INNER; countSol(now);
    CUR = OUTER; countSol(now);
}

int countSol(vector<string> _board) {
    addBoundary(_board);
    auto slither = newSlither();
    initalRules(slither);
    count_sol = 0;
    countSol(slither);
    return count_sol;
}
