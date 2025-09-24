#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;

unsigned n, maxx;
unsigned col, diag, codiag;
// bool col[30], diag[30], codiag[30];
vector<unsigned> board;
unsigned cnt = 0;

void solve(unsigned row) {
    if (row == n) {
        cnt++;
        // for (unsigned i = 0; i < n; ++i) {
        //     for (unsigned j = 0; j < n; ++j) {
        //         if (board[i] & (1 << j)) cout << "Q ";
        //         else cout << ". ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
        return;
    }
    unsigned tmp = (col | (diag >> row) | (codiag >> (n - row - 1))) & maxx;
    tmp = maxx ^ tmp;
    while(tmp) {
        unsigned j = lowbit(tmp);
        // board[row] = j;
        col |= j;
        diag |= j << row;
        codiag |= j << (n - row - 1);
        solve(row + 1);
        col ^= j;
        diag ^= j << row;
        codiag ^= j << (n - row - 1);
        tmp ^= j;
    }
}

int main() {
    cin >> n;
    maxx = (1 << n) - 1;
    col = diag = codiag = 0;
    board.resize(n);
    solve(0);
    cout << "Total solutions: " << cnt << "\n";
    return 0;
}

/*
目前人类已经计算出的极限是 27，表格如下
(来源: https://oeis.org/A000170)
n	a(n)
0	1
1	1
2	0
3	0
4	2
5	10
6	4
7	40
8	92
9	352
10	724
11	2680
12	14200
13	73712
14	365596
15	2279184
16	14772512
17	95815104
18	666090624
19	4968057848
20	39029188884
21	314666222712
22	2691008701644
23	24233937684440
24	227514171973736
25	2207893435808352
26	22317699616364044
27	234907967154122528
*/