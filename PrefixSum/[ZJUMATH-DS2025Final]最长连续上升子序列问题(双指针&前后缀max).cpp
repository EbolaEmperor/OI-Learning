#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// ---------------------------------------------------------
// 数据结构定义
// ---------------------------------------------------------
struct ArrayInfo {
    int id;         // 原始编号
    int max_lcis;   // 内部最长连续递增子序列
    int head_val;   // 首元素值
    int tail_val;   // 尾元素值
    int head_len;   // 前缀递增长度
    int tail_len;   // 后缀递增长度
    // 辅助字段
    int length;     
};

// 用于调试打印
void printInfo(const ArrayInfo& info) {
    cout << "{id:" << info.id 
         << " [" << info.head_val << "..." << info.tail_val << "]"
         << " hL:" << info.head_len << " tL:" << info.tail_len 
         << " max:" << info.max_lcis << "}";
}

// ---------------------------------------------------------
// 1. 优化算法 (修复后：Suffix Max + Two Pointers)
//    时间复杂度: O(N log N) (主要瓶颈在排序)
// ---------------------------------------------------------

// 辅助结构：记录某个范围内的最优和次优解（不同ID）
struct Top2 {
    int len1 = -1, id1 = -1; // 最优
    int len2 = -1, id2 = -1; // 次优（ID与最优不同）

    void update(int len, int id) {
        if (len > len1) {
            if (id != id1) {
                // 旧的最优降级为次优
                len2 = len1; 
                id2 = id1;
            }
            len1 = len;
            id1 = id;
        } else if (len > len2 && id != id1) {
            // 更新次优
            len2 = len;
            id2 = id;
        }
    }
};

bool cmpHead(const ArrayInfo& a, const ArrayInfo& b) {
    return a.head_val < b.head_val;
}

bool cmpTail(const ArrayInfo& a, const ArrayInfo& b) {
    return a.tail_val < b.tail_val;
}

int solveOptimized(const vector<ArrayInfo>& infoList) {
    int n = infoList.size();
    if (n < 2) return 0;

    int ans = 0;
    // 基础答案：单个数组内部的最大值
    for (const auto& list : infoList) {
        ans = max(ans, list.max_lcis);
    }

    vector<ArrayInfo> listH = infoList; // 作为后半段提供者
    vector<ArrayInfo> listT = infoList; // 作为前半段提供者

    // 1. 排序
    sort(listH.begin(), listH.end(), cmpHead); // 按 head_val 升序
    sort(listT.begin(), listT.end(), cmpTail); // 按 tail_val 升序

    // 2. 预处理后缀最大值
    // suffixTop[i] 表示 listH[i...n-1] 范围内的最长 head_len 信息
    vector<Top2> suffixTop(n + 1); 
    // 初始化末尾哨兵
    suffixTop[n] = {-1, -1, -1, -1};

    for (int i = n - 1; i >= 0; --i) {
        suffixTop[i] = suffixTop[i+1]; // 继承后面的信息
        suffixTop[i].update(listH[i].head_len, listH[i].id); //以此处元素更新
    }

    // 3. 双指针遍历
    // listT 的 tail_val 是递增的，所以满足 head_val > tail_val 的 listH 下标也是递增的
    int h_idx = 0; 
    
    for (const auto& itemT : listT) {
        // 找到第一个满足 listH[h_idx].head_val > itemT.tail_val 的位置
        // 因为 tail_val 变大，h_idx 只能向右移动（前面小的被淘汰）
        while (h_idx < n && listH[h_idx].head_val <= itemT.tail_val) {
            h_idx++;
        }

        if (h_idx >= n) break; // 没有任何一个 head_val 比当前 tail_val 大

        // 此时 listH[h_idx ... n-1] 都是合法的后半段候选
        // 我们直接查预处理好的后缀信息
        const Top2& best = suffixTop[h_idx];
        
        if (best.len1 != -1) {
            if (best.id1 != itemT.id) {
                ans = max(ans, itemT.tail_len + best.len1);
            } else {
                // 最优解ID冲突，尝试次优解
                if (best.len2 != -1) {
                    ans = max(ans, itemT.tail_len + best.len2);
                }
            }
        }
    }

    return ans;
}

// ---------------------------------------------------------
// 2. 暴力算法 O(N^2) (用于对拍验证)
// ---------------------------------------------------------
int solveNaive(const vector<ArrayInfo>& infoList) {
    int n = infoList.size();
    if (n < 2) return 0;

    int ans = 0;
    for (const auto& item : infoList) ans = max(ans, item.max_lcis);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // 必须是不同数组

            const ArrayInfo& A = infoList[i];
            const ArrayInfo& B = infoList[j];

            int current = max(A.max_lcis, B.max_lcis);
            
            // 尝试拼接
            if (A.tail_val < B.head_val) {
                current = max(current, A.tail_len + B.head_len);
            }
            ans = max(ans, current);
        }
    }
    return ans;
}

// ---------------------------------------------------------
// 3. 数据生成器
// ---------------------------------------------------------
ArrayInfo generateOne(int id, mt19937& rng) {
    ArrayInfo info;
    info.id = id;
    
    uniform_int_distribution<int> distLen(1, 500000);
    uniform_int_distribution<int> distVal(-1000, 1000); // 扩大范围减少碰撞
    
    info.length = distLen(rng);
    info.head_val = distVal(rng);
    info.tail_val = distVal(rng);

    uniform_int_distribution<int> distSubLen(1, info.length);
    info.head_len = distSubLen(rng);
    info.tail_len = distSubLen(rng);
    
    // 简单的合法性修正
    int min_max = max(info.head_len, info.tail_len);
    uniform_int_distribution<int> distMax(min_max, info.length);
    info.max_lcis = distMax(rng);

    return info;
}

vector<ArrayInfo> generateRandomData(int n) {
    random_device rd;
    mt19937 rng(rd());
    vector<ArrayInfo> data;
    for (int i = 0; i < n; ++i) {
        data.push_back(generateOne(i, rng));
    }
    return data;
}

// ---------------------------------------------------------
// 4. Main 对拍程序
// ---------------------------------------------------------
int main() {
    // 设置种子，方便复现 (如果需要随机，可以用 time(0))
    srand(time(0));
    
    int testCases = 5000; // 测试组数
    int n = 1000;          // 数组数量
    int successCount = 0;

    cout << "Starting Stress Test (Corrected Logic)..." << endl;

    for (int t = 1; t <= testCases; ++t) {
        // 生成数据
        vector<ArrayInfo> data = generateRandomData(n);

        // 运行两个算法
        int ansNaive = solveNaive(data);
        int ansOpt = solveOptimized(data);

        // 比较结果
        if (ansNaive != ansOpt) {
            cout << "\n[Mismatch Found!] Test Case #" << t << endl;
            cout << "Naive: " << ansNaive << ", Optimized: " << ansOpt << endl;
            cout << "Diff: " << ansNaive - ansOpt << endl;
            
            // 打印简要数据以供分析
            cout << "Data subset (Head/Tail info):" << endl;
            // 仅打印导致问题的可能对子会比较复杂，这里只打印前几个示意
            // 实际调试时可以导出到文件
            if (n <= 10) {
                for(auto& d : data) { printInfo(d); cout << endl; }
            }
            return 1; // 暂停
        } else {
            successCount++;
        }
        
        if (t % 500 == 0) cout << "Passed " << t << " cases..." << endl;
    }

    cout << "\nAll " << successCount << " cases passed! The algorithm is robust." << endl;
    return 0;
}
