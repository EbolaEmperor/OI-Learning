#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

const int N = 16;
int triesize[1 << N], prefix[1 << N];
int n, scnt[N][26];

int main(){
    cin >> n;
    memset(triesize, 0x3f, sizeof(triesize));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(char x : s)
            scnt[i][x - 'a']++;
        triesize[1 << i] = s.size();
    }
    for(int t = 0; t < (1 << n); t++){
        for(int c = 0; c < 26; c++){
            int mincnt = INT_MAX;
            for(int i = 0; i < n; i++)
                if(t >> i & 1) mincnt = min(mincnt, scnt[i][c]);
            prefix[t] += mincnt;
        }           
    }
    triesize[0] = 0;
    for(int t = 1; t < (1 << n); t++)
        for(int s = t & (t - 1); s; s = t & (s - 1))
            triesize[t] = min(triesize[t], triesize[s] + triesize[t ^ s] - prefix[t]);
    cout << triesize[(1 << n) - 1] + 1 << endl;
    return 0;
}