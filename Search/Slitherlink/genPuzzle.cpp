#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 rnd(rd());

int adj4[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

static inline vector<string> addBoundary(const vector<string> &_board) {
    int n = (int)_board.size();
    int m = (int)_board[0].size();
    vector<string> board;
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
    return board;
}

int main() {
    double rate;
    vector<string> grid;
    string line;
    cin >> rate;
    while(cin >> line) {
        grid.push_back(line);
    }
    int n = grid.size(), m = grid[0].size();
    grid = addBoundary(grid);
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if (rnd() < rate * rnd.max()) {
                int cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + adj4[k][0], nj = j + adj4[k][1];
                    if (grid[i][j] != grid[ni][nj]) ++cnt;
                }
                cout << cnt;
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}