#include<bits/stdc++.h>
using namespace std;

const int N=720;
bool s[N*N];
int len=0;

int main(int argc,char* argv[])
{
    freopen(argv[1],"rb",stdin);
    char ch;
    for(int i=0;i<43;i++) ch=fgetc(stdin);
    for(int i=0;i<715;i++)
    {
        for(int j=0;j<6;j++) ch=fgetc(stdin);
        for(int j=0;j<715;j++)
        {
            ch=fgetc(stdin);
            s[len++]=ch&1;
            ch=fgetc(stdin);
            ch=fgetc(stdin);
        }
    }
    int n=0,pos=32;
    for(int i=0;i<32;i++) n=n<<1|s[i];
    freopen("result.txt","w",stdout);
    for(int i=0;i<n;i++)
    {
        char x=0;
        for(int j=0;j<8;j++)
            x=x<<1|s[pos++];
        putchar(x);
    }
    return 0;
}