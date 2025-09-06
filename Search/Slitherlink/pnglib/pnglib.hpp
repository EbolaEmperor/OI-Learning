#pragma once

struct RGB{
    unsigned char r, g, b;
};

#define BLACK ((RGB){0,0,0})
#define WHITE ((RGB){255,255,255})
#define RED ((RGB){255,0,0})
#define GREEN ((RGB){0,255,0})
#define BLUE ((RGB){0,0,255})

class png
{
private:
    unsigned char *r, *g, *b;
    unsigned char *buffer;
    unsigned int len, n, m;
    void print(unsigned char x);
    void printi(unsigned int x);
    void alder32(unsigned char *v,int n);
    void crc(unsigned char *a,int n);
    void HEAD();
    void IHDR();
    void IDAT();
    void IEND();

public:
    png();
    png(const int &, const int &);
    png(const int &, const int &, const unsigned char*, const unsigned char*, const unsigned char*);
    ~png();
    void setpix(const int &, const int &, const unsigned char &, const unsigned char &, const unsigned char &);
    void setpix(const int &, const int &, const RGB &);
    void output(const char*);
};

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "miniz.hpp"

void png::print(unsigned char x)
{
    buffer[len++]=x;
}

void png::printi(unsigned int x)
{
    static unsigned char tmp[4];
    for(int i=0;i<4;i++) tmp[i]=x&255u,x>>=8u;
    for(int i=3;i>=0;i--) print(tmp[i]);
}

void png::alder32(unsigned char *v,int n)
{
    unsigned int a=1,b=0;
    for(int i=0;i<n;i++)
    {
        (a+=v[i])%=65521u;
        (b+=a)%=65521u;
    }
    printi(b*65536u+a);
}

void png::crc(unsigned char *a,int n)
{
    static const bool key[33]={1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,1};
    bool *bit;
    int len=0;
    bit = new bool [n*8+32];
    for(int i=0;i<n;i++)
    {
        unsigned char x=a[i];
        for(int j=0;j<8;j++)
            bit[len++]=x&1,x>>=1;
    }
    for(int i=0;i<32;i++) bit[len++]=0;
    for(int i=0;i<32;i++) bit[i]^=1;
    for(int i=0;i<n*8;i++)
    {
        while(i<n*8&&!bit[i]) i++;
        if(i>=n*8) break;
        for(int j=0;j<=32;j++)
            bit[i+j]^=key[j];
    }
    bool ans[32];
    for(int i=0;i<32;i++) ans[i]=bit[n*8+i]^1;
    std::reverse(ans,ans+32);
    unsigned char x;int pos=0;
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    x=0;for(int i=0;i<8;i++) x=x<<1|ans[pos++];print(x);
    delete [] bit;
}

void png::HEAD()
{
    print(0x89);print(0x50);print(0x4e);print(0x47);
    print(0x0d);print(0x0a);print(0x1a);print(0x0a);
}

void png::IHDR()
{
    print(0x00);print(0x00);print(0x00);print(0x0d);
    print(0x49);print(0x48);print(0x44);print(0x52);
    printi(m);printi(n);print(0x08);print(0x02);print(0x00);print(0x00);print(0x00);
    unsigned char tmp[17];
    for(int i=0;i<17;i++) tmp[i]=buffer[12+i];
    crc(tmp,17);
}

void png::IDAT()
{
    unsigned char *tmp;
    int tlen=0;
    tmp = new unsigned char [n+3*n*m];
    for(int i=0;i<n;i++)
    {
        tmp[tlen++]=0x00;
        for(int j=0;j<m;j++)
        {
            tmp[tlen++]=r[i*m+j];
            tmp[tlen++]=g[i*m+j];
            tmp[tlen++]=b[i*m+j];
        }
    }
    auto compressedLen = compressBound(tlen);
    unsigned char* compressedData = new unsigned char [compressedLen];
    compress(compressedData, &compressedLen, tmp, tlen);
    printi(compressedLen);
    unsigned char *buffer_bgin = buffer+len;
    print(0x49);print(0x44);print(0x41);print(0x54);
    memcpy(buffer+len, compressedData, compressedLen);
    len += compressedLen;
    crc(buffer_bgin, compressedLen+4);
    delete [] compressedData;
    delete [] tmp;
}

void png::IEND()
{
    print(0x00);print(0x00);print(0x00);print(0x00);
    print(0x49);print(0x45);print(0x4e);print(0x44);
    print(0xae);print(0x42);print(0x60);print(0x82);
}


png::png()
{
    n = m = len = 0;
    r = g = b = buffer = nullptr;
}

png::png(const int &N, const int &M)
{
    n = N;
    m = M;
    r = new unsigned char [n*m];
    g = new unsigned char [n*m];
    b = new unsigned char [n*m];
    memset(r, 0, n*m);
    memset(g, 0, n*m);
    memset(b, 0, n*m);
}

png::png(const int &N, const int &M, const unsigned char* R, const unsigned char* G, const unsigned char* B)
{
    n = N;
    m = M;
    r = new unsigned char [n*m];
    g = new unsigned char [n*m];
    b = new unsigned char [n*m];
    memcpy(r, R, (unsigned)n*m);
    memcpy(g, G, (unsigned)n*m);
    memcpy(b, B, (unsigned)n*m);
}

png::~png()
{
    buffer = nullptr;
    delete [] r;
    delete [] g;
    delete [] b;
    r = g = b = nullptr;
    len = n = m = 0;
}

void png::setpix(const int &row, const int &col, const unsigned char &R, const unsigned char &G, const unsigned char &B)
{
    if( row<0 || row>=n || col<0 || col>=m )
    {
        std::cerr << "PNG Error: setpix out of range " << std::endl;
        return;
    }
    r[row*m+col] = R;
    g[row*m+col] = G;
    b[row*m+col] = B;
}

void png::setpix(const int &row, const int &col, const RGB &color)
{
    setpix(row, col, color.r, color.g, color.b);
}

void png::output(const char* fname)
{
    len = 0;
    buffer = new unsigned char [n+3*n*m+64];
    HEAD();IHDR();IDAT();IEND();
    FILE *fout = fopen(fname,"wb");
    for(int i=0;i<len;i++) fputc(buffer[i],fout);
    fclose(fout);
    delete [] buffer;
    buffer = nullptr;
}
