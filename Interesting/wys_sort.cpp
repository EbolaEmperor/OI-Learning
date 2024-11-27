#include <iostream>
#include <random>
#define ui unsigned int
using namespace std;

void wys_sort(ui *a, int n){
    static ui c[256];
    ui *tmp = new ui[n];
    for(int u = 0; u < 32; u += 8){
        memset(c, 0, 4 * 256);
        for(int i = 0; i < n; i++) c[a[i]>>u&255]++;
        for(int i = 1; i < 256; i++) c[i] += c[i-1];
        for(int i = n - 1; i >= 0; i--) tmp[--c[a[i]>>u&255]] = a[i];
        memcpy(a, tmp, 4 * n);
    }
    delete[] tmp;
}

int main(){
    mt19937 rnd(19260817);
    const int n = 1e8;
    ui *a = new ui[n];
    for(int i = 0; i < n; i++)
        a[i] = rnd();
    
    int c = clock();
    wys_sort(a, n);
    cout << "sort time: " << (double) (clock()-c) / CLOCKS_PER_SEC << endl;

    for(int i = 0; i < n - 1; i++)
        if(a[i] > a[i + 1]) cout << "wrong!!!" << endl;
    return 0;
}