#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
#include <ctime>
#include <deque>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

const int ML = 200000000;
char mem[ML];
int ptr = 0;

void *operator new(size_t x){
    ptr += x;
    assert(ptr <= ML);
    return mem + ptr - x;
}

void operator delete(void *){}

static const int buf_size = 4096;

inline int getChar(){
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if(pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if(pos == len)
        return -1;
    return buf[pos++];
}

inline int readChar(){
    int c = getChar();
    while(c <= 32)
        c = getChar();
    return c;
}

inline int readInt(){
    int s = 1, c = readChar();
    int x = 0;
    if(c == '-')
        s = -1, c = getChar();
    while('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a[100], b[100];
    memset(a, 0, sizeof(a));
    memset(a, 0x7f, sizeof(a)); // 0x7f7f7f7f == 2139062143
    memcpy(b, a, sizeof(a)); // copy a to b
    memcmp(a, b, sizeof(a)); // compare a with b
    while(clock() < 0.95 * CLOCKS_PER_SEC){
        // do someting stupid...
    }
    const int size = 72321;
    array<int, size> c; //vector<int> c(size);
    vector<int> d;
    d.reserve(1000000);// reserve memory for d.push_back
    d.shrink_to_fit();// dereserve void memory
    unordered_map<int, int> e; // vector<int> e for sparse vector need less memory
    mt19937 rd(228);
    shuffle(d.begin(), d.end(), rd);

    return 0;
}
