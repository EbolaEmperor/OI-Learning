#include<bits/stdc++.h>
#include "combo.h"
using namespace std;

string guess_sequence(int n)
{
    static char ch[4]={'A','B','X','Y'};
    static string ans;
    if(press("AB")) press("A")?void():swap(ch[0],ch[1]);
    else press("X")?swap(ch[0],ch[2]):swap(ch[0],ch[3]);
    ans+=ch[0];
    if(n==1) return ans;
    for(int i=2;i<n;i++)
    {
        int len=press(ans+ch[1]+ch[1]+ans+ch[1]+ch[2]+ans+ch[1]+ch[3]+ans+ch[2]);
        if(len==i+1) ans+=ch[1];
        else if(len==i) ans+=ch[2];
        else ans+=ch[3];
    }
    if(press(ans+ch[1])==n) return ans+ch[1];
    if(press(ans+ch[2])==n) return ans+ch[2];
    return ans+ch[3];
}