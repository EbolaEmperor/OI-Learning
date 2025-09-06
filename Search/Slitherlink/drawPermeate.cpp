#include <bits/stdc++.h>
using namespace std;

// from permeate.cpp
vector<vector<uint8_t>> permeate(int H, int W, bool draw = false);

int main(int argc, char **argv) {
    int H = 16, W = 16;
    if (argc >= 3) {
        H = atoi(argv[1]);
        W = atoi(argv[2]);
    }
    auto g = permeate(H, W, true);
    return 0;
}