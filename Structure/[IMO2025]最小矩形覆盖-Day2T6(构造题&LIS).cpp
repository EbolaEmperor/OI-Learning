#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long k;
    if (!(cin >> k)) return 0;
    long long N = k * k;

    // m = (k-1)^2 + 4*(k-1) = k^2 + 2k - 3
    long long m = (k == 1 ? 0 : (k*k + 2*k - 3));
    cout << m << "\n";

    // k=1 特判：唯一的 1x1 网格是洞
    if (k == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // 网格 1..N，先清零（0 表示洞/未覆盖）
    vector<int> grid(N * N, 0);
    auto at = [&](long long r, long long c) -> int& {
        return grid[(r-1)*N + (c-1)];
    };

    long long next_id = 1;

    // 一、放置 (k-1)^2 个 k×k 正方形
    // 第 (i,j) 个的左上角：r0 = i*k - (j-1), c0 = (j-1)*k + i + 1
    for (long long i = 1; i <= k-1; ++i) {
        for (long long j = 1; j <= k-1; ++j) {
            long long r0 = i * k - (j - 1);
            long long c0 = (j - 1) * k + i + 1;
            // 覆盖 r0..r0+k-1, c0..c0+k-1
            for (long long r = r0; r <= r0 + k - 1; ++r) {
                for (long long c = c0; c <= c0 + k - 1; ++c) {
                    // 设计保证不重叠，如要保险可加断言：if(at(r,c)!=0) abort();
                    at(r, c) = (int)next_id;
                }
            }
            ++next_id;
        }
    }

    // 二、四组宽度为 1 的长条（每条用一个新编号）
    auto place_hbar = [&](long long row, long long L, bool from_left) {
        long long id = next_id++;
        if (from_left) {
            for (long long c = 1; c <= L; ++c) at(row, c) = (int)id;
        } else {
            for (long long c = N - L + 1; c <= N; ++c) at(row, c) = (int)id;
        }
    };
    auto place_vbar = [&](long long col, long long L, bool from_top) {
        long long id = next_id++;
        if (from_top) {
            for (long long r = 1; r <= L; ++r) at(r, col) = (int)id;
        } else {
            for (long long r = N - L + 1; r <= N; ++r) at(r, col) = (int)id;
        }
    };

    for (long long i = 1; i <= k-1; ++i) {
        long long L = k * (k - i); // L decreases by k
        // 顶边：第 i 行，从左开始长度 L
        place_hbar(i, L, /*from_left=*/true);
        // 右边：第 N-i+1 列，从顶开始长度 L
        place_vbar(N - i + 1, L, /*from_top=*/true);
        // 底边：第 N-i+1 行，从右开始长度 L
        place_hbar(N - i + 1, L, /*from_left=*/false);
        // 左边：第 i 列，从底开始长度 L
        place_vbar(i, L, /*from_top=*/false);
    }

    // 输出网格
    for (long long r = 1; r <= N; ++r) {
        for (long long c = 1; c <= N; ++c) {
            if (c > 1) cout << ' ';
            cout << at(r, c);
        }
        cout << '\n';
    }
    return 0;
}