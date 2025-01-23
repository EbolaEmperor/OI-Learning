#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <iomanip>
#include <stack>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdlib>
using namespace std;

void err(){
    cout << "ILLEGAL" << endl;
    exit(-1);
}

struct Node{
    bool isnum;
    char op;
    double num;
};
Node newNum(double x){return (Node){true, ' ', x};}
Node newOp(char c){return (Node){false, c, 0};}
vector<Node> sufexpr;
stack<char> op;

int prio(char c){
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/') return 2;
    else if(c == '^') return 3;
    else return 0;
}

void deal(int pri){
    while(!op.empty() && prio(op.top()) >= pri){
        if(op.top() == '('){
            op.pop();
            break;
        }
        sufexpr.push_back(newOp(op.top()));
        op.pop();
    }
}

void output(){
    for(Node p : sufexpr){
        if(p.isnum) printf("%lf ", p.num);
        else printf("%c ", p.op);
    }
    printf("\n");
}

double calc(double a, double b, char c){
    if(c == '+') return a + b;
    else if(c == '-') return a - b;
    else if(c == '*') return a * b;
    else if(c == '/'){
        if(b == 0) err();
        return a / b;
    }
    else return pow(a, b);
}

void oneStep(){
    int i = 0;
    while(sufexpr[i].isnum) i++;
    double x = calc(sufexpr[i-2].num, sufexpr[i-1].num, sufexpr[i].op);
    sufexpr[i-2].num = x;
    sufexpr.erase(sufexpr.begin() + (i-1), sufexpr.begin() + (i+1));
}

double compute(){
    stack<double> num;
    for(auto e : sufexpr){
        if(e.isnum) num.push(e.num);
        else {
            if(num.size() < 2) err();
            double b = num.top(); num.pop();
            double a = num.top(); num.pop();
            num.push(calc(a, b, e.op));
        }
    }
    if(num.size() != 1) err();
    return num.top();
}

int main(){
    string s;
    cin >> s;
    s += '#';
    int pos = 0;
    char c = s[0];
    int brLevel = 0;
    while(c != '#'){
        if(!isdigit(c) && !(c == '-' && !(isdigit(s[pos-1]) || s[pos-1] == ')'))){
            if(c != '^' && c != '(') deal(prio(c));
            if(c != ')') op.push(c);
            if(c == '(') ++brLevel;
            if(c == ')' && !brLevel--) err();
            c = s[++pos];
        } else {
            double x = 0, fg = 1;
            if(c == '-') fg = -1, c = s[++pos];
            while(c >= '0' && c <= '9'){
                x = x * 10 + (c - '0');
                c = s[++pos];
            }
            if(c == '.'){
                double pw = 1;
                c = s[++pos];
                while(c >= '0' && c <= '9'){
                    pw /= 10;
                    x += pw * (c - '0');
                    c = s[++pos];
                }
            }
            if(c == 'e'){
                c = s[++pos];
                int efg = 1;
                if(c == '+' || c == '-'){
                    if(c == '-') efg = -1;
                    c = s[++pos];
                }
                int ex = 0;
                while(c >= '0' && c <= '9'){
                    ex = ex * 10 + (c - '0');
                    c = s[++pos];
                }
                x = x * pow(10.0, ex * efg);
            }
            sufexpr.push_back(newNum(x * fg));
        }
    }
    if(brLevel) err();
    deal(1);
    cout << setprecision(12) << compute() << endl;
    return 0;
}