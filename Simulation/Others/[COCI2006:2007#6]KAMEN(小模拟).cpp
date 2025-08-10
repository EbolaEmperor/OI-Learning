#include <bits/stdc++.h>
using namespace std;

const int R = 30010, C = 35;
// paths[i]: 从 (1,i) 开始的路径自上而下依次经过的列编号
vector<int> paths[C];
char a[R][C];
int r, c;

void update(vector<int> &path) {
   while (true) {
      int i = path.size(), j = path.back();
      if (a[i][j] != '.') path.pop_back();
      else if (a[i+1][j] == '.') path.push_back(j);
      else if (i == r || a[i+1][j] == 'X') break;
      else {
         if (j > 1 && a[i][j-1] == '.' && a[i+1][j-1] == '.') path.push_back(j-1);
         else if(j < c && a[i][j+1] == '.' && a[i+1][j+1] == '.') path.push_back(j+1);
         else break;
      }
   }
}

int main() {
   scanf("%d%d", &r, &c);
   for (int i = 1; i <= r; i++)
      scanf("%s", a[i] + 1);
   for (int i = 1; i <= c; i++) {
      paths[i].push_back(i);
      update(paths[i]);
   }
   int n, x;
   scanf("%d", &n);
   while(n--) {
      scanf("%d", &x);
      a[paths[x].size()][paths[x].back()] = 'O';
      for(int i = 1; i <= c; i++) update(paths[i]);
   }
   for (int i = 1; i <= r; i++)
      printf("%s\n", a[i] + 1);
   return 0;
}