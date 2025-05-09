/*****************************************************************
 * CF 2094H  La Vaca Saturno Saturnita
 *
 * 实现思路（对应题主给出的方案）：
 *   1. 设阈值 B = ⌈√MAXA⌉ (MAXA = 1e5 → B = 320)。
 *   2. 小因子 (≤B)：预处理 nxt[i][d] 表示从 i 开始往右第一个
 *      a[j] == d 的位置，用于 O(1) 查询。
 *   3. 大因子 (>B)：
 *        预处理 pos[k] —— 所有 a[i] > B 且能整除 k 的下标集合。
 *        方法：枚举数组中每个 “大数” v，在线性枚举其倍数
 *        m = v, 2v, … ≤ MAXA，把下标 i 插入 pos[m]。
 *        一个下标最多插入 ⌈MAXA / (B+1)⌉ ≈ 312 次，
 *        故总体复杂度 O(n·MAXA/B)。
 *   4. 查询：
 *        双指针 cur 扫描区间 [l,r]，val 保存当前 k。
 *        每次用
 *          • 小因子：枚举 val 的所有因子 ≤ B，用 nxt 取最小下标；
 *          • 大因子：直接在 pos[val] 里 lower_bound(cur)。
 *        得到最近的改变位置 idx，把 (idx-cur)×val 累加进答案，
 *        然后在 idx 处更新 val，并继续循环。
 *
 *   总复杂度：
 *     预处理  O(nB + n·MAXA/B)
 *     单次查询 O(∑(#因子(val)) · log n)   (最多 log₂k 轮)
 *****************************************************************/

 #include <bits/stdc++.h>
 using namespace std;
 
 const int MAXA = 100000;      // a[i] 和 k 的最大值
 const int B     = 320;        // ⌈√MAXA⌉
 
 // divisors[x] : x 的全部正因子
 static vector<int> divisors[MAXA + 1];
 // pos[k]      : 所有满足 a[i] > B 且 k % a[i] == 0 的下标 i (升序)
 // 由于多测试用例，需要清理，用 static 并记录 touched 列表
 static vector<int> pos[MAXA + 1];
 static vector<int> touched;
 
 int main() {
     ios::sync_with_stdio(false);
     cin.tie(nullptr);
 
     /* -------- 全局预处理：每个数的因子 -------- */
     for (int d = 1; d <= MAXA; ++d)
         for (int m = d; m <= MAXA; m += d)
             divisors[m].push_back(d);
 
     int T;  cin >> T;
     while (T--) {
         int n, q;  cin >> n >> q;
         vector<int> a(n + 1);
         for (int i = 1; i <= n; ++i) cin >> a[i];
 
         /* -------- 构建 pos[k] -------- */
         touched.clear();
         for (int i = 1; i <= n; ++i) if (a[i] > B) {
             int v = a[i];
             for (int m = v; m <= MAXA; m += v) {
                 if (pos[m].empty()) touched.push_back(m);
                 pos[m].push_back(i);
             }
         }
 
         /* -------- 预处理小因子 nxt 表 -------- */
         vector<array<int, B + 1>> nxt(n + 2);
         for (int d = 1; d <= B; ++d) nxt[n + 1][d] = n + 1; // 哨兵
         for (int i = n; i >= 1; --i) {
             nxt[i] = nxt[i + 1];          // 复制下一行
             if (a[i] <= B) nxt[i][a[i]] = i;
         }
 
         /* -------- 回答查询 -------- */
         while (q--) {
             int k, l, r;
             cin >> k >> l >> r;
             long long ans = 0;
             int cur = l;
             int val = k;
 
             while (cur <= r) {
                 int idx = r + 1;      // 默认找不到
 
                 /* ---- 1) 小因子 ---- */
                 for (int d : divisors[val]) {
                     if (d > B) break;           // 后面因子已 >B
                     if (d >= 2) {               // a[i] ≥ 2，因子 1 无需考虑
                         int cand = nxt[cur][d];
                         if (cand < idx) idx = cand;
                     }
                 }
 
                 /* ---- 2) 大因子 ---- */
                 auto &vec = pos[val];
                 if (!vec.empty()) {
                     auto it = lower_bound(vec.begin(), vec.end(), cur);
                     if (it != vec.end() && *it < idx) idx = *it;
                 }
 
                 /* ---- 累加答案 & 更新 ---- */
                 if (idx > r) {                  // 之后 k 不再变化
                     ans += 1LL * (r - cur + 1) * val;
                     break;
                 } else {
                     ans += 1LL * (idx - cur) * val; // [cur, idx-1] 贡献
                     while (val % a[idx] == 0) val /= a[idx]; // 在 idx 处更新 k
                     cur = idx;              // 跳到下一段
                 }
             }
             cout << ans << '\n';
         }
 
         /* -------- 清理 pos -------- */
         for (int m : touched) pos[m].clear();
     }
     return 0;
 }