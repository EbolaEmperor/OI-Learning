#include <bits/stdc++.h>
using namespace std;

// from permeate.cpp
vector<vector<uint8_t>> permeate(int H, int W, bool draw = false);

// from slitherlink.cpp
int countSol(vector<string> _board);

vector<string> genNumber(vector<string> grid) {
    random_device rddd;
    mt19937 rng(rddd() + 114514);

    const int adj4[][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    auto numGrid = grid;
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int cnt = 0;
            for (int k = 0; k < 4; k++) {
                int ni = i + adj4[k][0], nj = j + adj4[k][1];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) cnt += (grid[i][j] == '*');
                else cnt += (grid[i][j] != grid[ni][nj]);
            }
            numGrid[i][j] = '0' + cnt;
        }
    }

    // 在确保解唯一性的前提下删除至少一半的数字
    int del_cnt = 0, stop = 0;
    while (del_cnt < 0.5 * n * m) {
        int i, j;
        do {
            i = rng() % n, j = rng() % m;
        } while(numGrid[i][j] == '.');
        auto x = numGrid[i][j];
        numGrid[i][j] = '.';
        if (countSol(numGrid) == 1) {
            ++del_cnt;
            stop = 0;
        } else {
            numGrid[i][j] = x;
            // 如果超过 20 次删除无效，直接退出
            if (++stop > 20) break;
        }
    }

    return numGrid;
}


int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int H = 16, W = 16;
    if (argc >= 3)
    {
        H = atoi(argv[1]);
        W = atoi(argv[2]);
    }
    auto g = permeate(H, W);

    vector<string> gg;
    for (int r = 0; r < H; r++)
    {
        string line;
        for (int c = 0; c < W; c++)
            line += (g[r][c] ? '*' : '.');
        gg.push_back(line);
    }
    
    auto numGrid = genNumber(gg);
    for (auto &s : numGrid)
        cout << s << "\n";

    return 0;
}
