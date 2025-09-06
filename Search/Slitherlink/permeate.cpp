// Permeate: build the wiggly line via two-color flips
// It follows the article’s rules exactly:
//   Wiggliness rule:
//     same(O) > diff(O) OR (same(O) == diff(O) AND same(D) > diff(D))
//   Connectivity rule:
//     Let flips be the number of color changes around the 8-neighbour ring (in spatial order).
//     Let num(O) be the number of in-bounds orthogonal neighbours (2/3/4).
//     Forbid the flip if: flips > 2 * num(O) - 4
// url: https://liamappelbe.medium.com/how-to-generate-slither-link-puzzles-6c65510b2ba1

#include <bits/stdc++.h>
#include "pnglib/pnglib.hpp"
using namespace std;

struct Pt
{
    int r, c;
};
static const int DR4[4] = {-1, 1, 0, 0};
static const int DC4[4] = {0, 0, -1, 1};
static const int DR8[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
static const int DC8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

inline bool inb(int r, int c, int R, int C) { return r >= 0 && r < R && c >= 0 && c < C; }

// Count orthogonal/diagonal same & diff against center color
static void count_O_D(const vector<vector<uint8_t>> &g, int r, int c,
                      int &sameO, int &diffO, int &sameD, int &diffD, int &numO)
{
    int R = g.size(), C = g[0].size();
    uint8_t col = g[r][c];
    sameO = diffO = sameD = diffD = 0;
    numO = 0;
    for (int k = 0; k < 4; k++)
    {
        int nr = r + DR4[k], nc = c + DC4[k];
        if (inb(nr, nc, R, C))
        {
            numO++;
            if (g[nr][nc] == col)
                sameO++;
            else
                diffO++;
        }
    }
    for (int k = 0; k < 4; k++)
    {
        int nr = r + (k == 0 ? -1 : k == 1 ? -1
                                : k == 2   ? 1
                                           : 1);
        int nc = c + (k == 0 ? -1 : k == 1 ? 1
                                : k == 2   ? 1
                                           : -1);
        if (inb(nr, nc, R, C))
        {
            if (g[nr][nc] == col)
                sameD++;
            else
                diffD++;
        }
    }
}

// Compute flips around the 8-neighbour ring using only in-bounds neighbours, in spatial order
static int ring_flips(const vector<vector<uint8_t>> &g, int r, int c)
{
    int R = g.size(), C = g[0].size();
    vector<uint8_t> ring;
    ring.reserve(8);
    for (int k = 0; k < 8; k++)
    {
        int nr = r + DR8[k], nc = c + DC8[k];
        if (inb(nr, nc, R, C))
            ring.push_back(g[nr][nc]);
    }
    if (ring.size() < 2)
        return 0;
    int flips = 0;
    for (size_t i = 0; i < ring.size(); ++i)
        if (ring[i] != ring[(i + 1) % ring.size()])
            ++flips;
    return flips;
}

// Boundary test: shares at least one orthogonal edge with opposite color
static bool is_boundary_cell(const vector<vector<uint8_t>> &g, int r, int c)
{
    int R = g.size(), C = g[0].size();
    uint8_t col = g[r][c];
    for (int k = 0; k < 4; k++)
    {
        int nr = r + DR4[k], nc = c + DC4[k];
        if (inb(nr, nc, R, C) && g[nr][nc] != col)
            return true;
    }
    return false;
}

// Robust connectedness + no-holes checks for colour=1 (#)
static bool ones_connected_4(const vector<vector<uint8_t>> &a)
{
    int H = a.size(), W = a[0].size();
    int tot = 0;
    Pt s{-1, -1};
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            if (a[r][c])
            {
                ++tot;
                if (s.r == -1)
                    s = {r, c};
            }
    if (tot == 0)
        return false; // require non-empty
    vector<vector<char>> vis(H, vector<char>(W, 0));
    queue<Pt> q;
    q.push(s);
    vis[s.r][s.c] = 1;
    int seen = 0;
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        ++seen;
        for (int k = 0; k < 4; k++)
        {
            int nr = u.r + DR4[k], nc = u.c + DC4[k];
            if (nr < 0 || nc < 0 || nr >= H || nc >= W)
                continue;
            if (a[nr][nc] && !vis[nr][nc])
            {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
    return seen == tot;
}

// No-holes for # region: ensure all 0-cells are reachable from boundary via 4-neighbour paths in 0-cells
static bool zeros_all_from_border(const vector<vector<uint8_t>> &a)
{
    int H = a.size(), W = a[0].size();
    vector<vector<char>> vis(H, vector<char>(W, 0));
    queue<Pt> q;
    auto push = [&](int r, int c)
    {
        if (r < 0 || c < 0 || r >= H || c >= W)
            return;
        if (a[r][c] != 0 || vis[r][c])
            return;
        vis[r][c] = 1;
        q.push({r, c});
    };
    for (int i = 0; i < W; i++) push(0, i), push(H-1, i);
    for (int i = 0; i < H; i++) push(i, 0), push(i, W-1);
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (int k = 0; k < 4; k++)
            push(u.r + DR4[k], u.c + DC4[k]);
    }
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            if (a[r][c] == 0 && !vis[r][c])
                return false; // 0-island => hole in #
    return true;
}

// Try flipping (r,c) and keep only if all guards pass; otherwise revert
static bool try_flip_keep_if_good(vector<vector<uint8_t>> &g, int r, int c, int numO)
{
    g[r][c] ^= 1; // tentative
    bool ok = ones_connected_4(g) && zeros_all_from_border(g);
    if (!ok)
        g[r][c] ^= 1; // revert
    return ok;
}

// The step-1 generator (two-colour flip process) with strict invariants
vector<vector<uint8_t>> permeate(int H, int W, bool draw = false)
{
    random_device rddd;
    mt19937 rng(rddd());
    int R = H, C = W;
    vector<vector<uint8_t>> g(R, vector<uint8_t>(C, 0));

    // Initial colouring: top half 0, bottom half 1
    uint8_t lenH = ceil(H / sqrt(3)), stH = (H - lenH) / 2;
    uint8_t lenW = ceil(W / sqrt(3)), stW = (W - lenW) / 2;
    for (int r = stH; r < stH + lenH; r++)
        for (int c = stW; c < stW + lenW; c++)
            g[r][c] = 1;
    for (int r = 0; r < stH + 2; r++)
        for (int c = 0; c < stW + 2; c++)
            g[r][c] = 1;

    // Frontier
    vector<Pt> cand;
    cand.reserve(R * C);
    vector<vector<uint8_t>> inq(R, vector<uint8_t>(C, 0));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (is_boundary_cell(g, r, c))
            {
                cand.push_back({r, c});
                inq[r][c] = 1;
            }
    
    if (draw) {
        mkdir("FigPerme", 0755);
    }
    int picid = 0;

    while (!cand.empty())
    {
        uniform_int_distribution<int> dist(0, (int)cand.size() - 1);
        int idx = dist(rng);
        Pt p = cand[idx];
        cand[idx] = cand.back();
        cand.pop_back();
        inq[p.r][p.c] = 0;
        if (!is_boundary_cell(g, p.r, p.c))
            continue;

        int sameO, diffO, sameD, diffD, numO;
        count_O_D(g, p.r, p.c, sameO, diffO, sameD, diffD, numO);
        bool wiggle_ok = (sameO > diffO) || (sameO == diffO && sameD > diffD);
        if (!wiggle_ok)
            continue;

        int flips = ring_flips(g, p.r, p.c);
        if (flips > 2 * numO - 4)
            continue; // topology guard

        // strict invariants: keep flip only if # stays 4-connected and hole-free
        if (try_flip_keep_if_good(g, p.r, p.c, numO))
        {
            for (int k = 0; k < 4; k++)
            {
                int nr = p.r + DR4[k], nc = p.c + DC4[k];
                if (inb(nr, nc, R, C) && !inq[nr][nc])
                {
                    cand.push_back({nr, nc});
                    inq[nr][nc] = 1;
                }
            }
        }

        if (draw)
        {
            png pic(H, W);
            for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++) {
                    pic.setpix(i, j, g[i][j] ? BLACK : WHITE);
                }
            stringstream fname;
            fname << "FigPerme/step" << setw(5) << setfill('0') << picid << ".png";
            pic.output(fname.str().c_str());
            ++picid;
        }
    }
    return g;
}