#include <iostream>
#include <cstring>
using namespace std;

const int N = 100010;
int cnta[N][2], idxa[N], tota;
int cntb[N][2], idxb[N], totb;
string a, swpa, b, swpb;

int work(){
    int n;
    cin >> n;
    cin >> a >> b >> swpa >> swpb;
    tota = totb = 0;
    memset(cnta, 0, sizeof(cnta));
    memset(cntb, 0, sizeof(cntb));
    for(int i = 0; i < n; i++){
        if(i == 0 || swpa[i] == '0' || swpa[i - 1] == '0') ++tota;
        if(i == 0 || swpb[i] == '0' || swpb[i - 1] == '0') ++totb;
        idxa[i] = tota;
        idxb[i] = totb;
        cnta[tota][a[i]-'0']++;
        cntb[totb][b[i]-'0']++;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        int ida = idxa[i], idb = idxb[i];
        if(cnta[ida][0] && cntb[idb][0]) ans++, cnta[ida][0]--, cntb[idb][0]--;
        else if(cnta[ida][1] && cntb[idb][1]) ans++, cnta[ida][1]--, cntb[idb][1]--;
        else if(cnta[ida][0] && cntb[idb][1]) cnta[ida][0]--, cntb[idb][1]--;
        else if(cnta[ida][1] && cntb[idb][0]) cnta[ida][1]--, cntb[idb][0]--;
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    while(T--) cout << work() << endl;
    return 0;
}