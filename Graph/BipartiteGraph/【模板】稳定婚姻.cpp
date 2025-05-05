#include <bits/stdc++.h>
#include <numeric>
using namespace std;

class StableMarriage {
private:
    int n;
    vector<vector<int>> men;
    vector<vector<int>> women;
    vector<int> wPartner;
    vector<int> mPartner;
    vector<vector<int>> rank;
    
public:
    StableMarriage(int n, const vector<vector<int>>& menPrefs, const vector<vector<int>>& womenPrefs) : n(n) {
        men = menPrefs;
        women = womenPrefs;
        wPartner.resize(n, -1);
        mPartner.resize(n, -1);
        rank.resize(n, vector<int>(n, -1));
        for (int w = 0; w < n; w++) {
            for (int i = 0; i < n; i++) {
                int m = women[w][i];
                rank[w][m] = i;
            }
        }
    }
    
    bool isStable(const vector<int>& mMatches) {
        if ((int)mMatches.size() != n) return false;
        
        vector<int> wMatches(n, -1);
        for (int m = 0; m < n; m++) {
            int w = mMatches[m];
            if (w != -1) {
                if (w < 0 || w >= n) return false;
                wMatches[w] = m;
            }
        }
        
        vector<vector<int>> mRank(n, vector<int>(n, -1));
        for (int m = 0; m < n; m++) {
            for (int i = 0; i < n; i++) {
                int w = men[m][i];
                mRank[m][w] = i;
            }
        }
        
        for (int m = 0; m < n; m++) {
            int w1 = mMatches[m];
            if (w1 == -1) continue;
            for (int w = 0; w < n; w++) {
                if (w == w1) continue;
                int m1 = wMatches[w];
                if (m1 == -1) continue;
                if (mRank[m][w] < mRank[m][w1] && rank[w][m] < rank[w][m1]) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    void solve() {
        queue<int> freeM;
        for (int i = 0; i < n; i++) freeM.push(i);
        vector<int> nextProp(n, 0);
        // Gale-Sharpley 算法 （男士求婚算法）
        while (!freeM.empty()) {
            int m = freeM.front(); freeM.pop();
            int w = men[m][nextProp[m]++];
            if (wPartner[w] == -1) {
                wPartner[w] = m;
                mPartner[m] = w;
            } else {
                int m1 = wPartner[w];
                if (rank[w][m] < rank[w][m1]) {
                    wPartner[w] = m;
                    mPartner[m] = w;
                    mPartner[m1] = -1;
                    freeM.push(m1);
                } else {
                    freeM.push(m);
                }
            }
        }
    }
    
    pair<vector<int>, vector<int>> getMatches() {
        return make_pair(mPartner, wPartner);
    }
};

int main(){
    int n;
    cin >> n;
    
    vector<vector<int>> menPrefs(n, vector<int>(n));
    vector<vector<int>> womenPrefs(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> menPrefs[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> womenPrefs[i][j];
        }
    }
    
    StableMarriage sm(n, menPrefs, womenPrefs);
    sm.solve();
    
    vector<int> result = sm.getMatches().first;
    cout << "Gale-Sharpley Algorithm Result:" << endl;
    for (int i = 0; i < n; i++) {
        cout << result[i] << (i == n-1 ? "\n" : " ");
    }
    cout << "Is the result stable? " 
         << (sm.isStable(result) ? "Yes" : "No") << endl;
    cout << "----------------------------------------------" << endl;

    if (n <= 8) {
        vector<int> mMatches(n);
        iota(mMatches.begin(), mMatches.end(), 0);
        do {
            if (sm.isStable(mMatches)) {
                cout << "Stable Matching: ";
                for (int i = 0; i < n; i++) {
                    cout << mMatches[i] << (i == n-1 ? "\n" : " ");
                }
            }
        } while(next_permutation(mMatches.begin(), mMatches.end()));
    }
    
    return 0;
}