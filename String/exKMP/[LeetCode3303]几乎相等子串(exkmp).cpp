class Solution {
private:
    int n, m;
    vector<int> z1, z2;
public:
    void get_z(const string &s, vector<int> &z){
        int n = s.size() - 1;
        z.resize(n + 1);
        int l = 1, r = 1;
        for(int i = 2; i <= n; i++){
            z[i] = (i <= r) ? min(z[i-l+1], r-i+1) : 0;
            // 注意：当 i<=r 且 z[i-l+1]<r-i+1 时，while 循环一定不会执行
            while(i+z[i] <= n && s[1+z[i]] == s[i+z[i]]) z[i]++;
            if(i+z[i]-1 > r) l = i, r = i+z[i]-1;
        }
        z[1] = n;
    }
    int minStartingIndex(string s, string pattern) {
        int m = pattern.size();
        string t1 = ' ' + pattern + '#' + s;
        get_z(t1, z1);
        z1.erase(z1.begin(), z1.begin() + m + 2);
        string t2 = s + '#' + pattern + ' ';
        reverse(t2.begin(), t2.end());
        get_z(t2, z2);
        z2.erase(z2.begin(), z2.begin() + m + 2);
        reverse(z2.begin(), z2.end());
        int n = s.size();
        for(int i = 0; i + m - 1 < n; i++)
            if(z1[i] + z2[i + m - 1] + 1 >= m) return i;
        return -1;
    }
};