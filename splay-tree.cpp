#include <unordered_set>
#include <unordered_map>
#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <random>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

struct Node{

    Node* l = nullptr, *r = nullptr, *pr = nullptr;
    int v, mn;

    Node(){
        v = 0;
        mn = 0;
    }

    Node(int v): v(v), mn(v){}

};

void zig(Node* x, Node* p){
    Node* pr = p->pr;
    if(pr!=nullptr){
        if(pr->l==p)
            pr->l = x;
        else
            pr->r = x;
    }
    if(p->l==x){
        if(x->r!=nullptr)
            x->r->pr = p;
        p->l = x->r;
        x->r = p;
    }
    else{
        if(x->l!=nullptr)
            x->l->pr = p;
        p->r = x->l;
        x->l = p;
    }
    p->pr = x;
    x->pr = pr;
}

void zig_zig(Node* x, Node* p, Node* g){
    zig(p, g);
    zig(x, p);
}

void zig_zag(Node* x, Node* p, Node* g){
    zig(x, p);
    zig(x, g);
}

bool is_l(Node* x, Node* p){
    return (p->l==x);
}

void print(Node* a){
    if(a==nullptr)
        return;
    print(a->l);
    cout << a->v << ' ';
    print(a->r);
}

Node* splay(Node* x){
    while(x->pr!=nullptr){
        if(x->pr->pr==nullptr){
            zig(x, x->pr);
            continue;
        }
        if(is_l(x, x->pr)==is_l(x->pr, x->pr->pr)){
            zig_zig(x, x->pr, x->pr->pr);
        }
        else{
            zig_zag(x, x->pr, x->pr->pr);
        }
    }
    return x;
}

Node* get_min(Node* a){
    if(a==nullptr||a->l==nullptr)
        return a;
    return get_min(a->l);
}

Node* get_max(Node* a){
    if(a==nullptr||a->r==nullptr)
        return a;
    return get_max(a->r);
}

Node* merge(Node* a, Node* b){
    if(a==nullptr&&b==nullptr)
        return nullptr;
    if(a==nullptr){
        b = splay(get_min(b));
        b->l = a;
        return b;
    }
    a = splay(get_max(a));
    a->r = b;
    if(b!=nullptr)
        b->pr = a;
    return a;
}

Node* find(Node* a, int v){
    if(a==nullptr)
        return nullptr;
    if(a->v==v)
        return a;
    if((a->v)>v){
        if(a->l==nullptr)
            return nullptr;
        return find(a->l, v);
    }
    if(a->r==nullptr)
        return a;
    Node* kek = find(a->r, v);
    if(kek==nullptr)
        return a;
    return kek;
}

pair<Node*, Node*> split(Node* a, int v){
    Node* ret = find(a, v);
    if(ret==nullptr)
        return make_pair(nullptr, a);
    a = splay(ret);
    pair<Node*, Node*> kek = make_pair(a, a->r);
    if(a->r!=nullptr)
        a->r->pr = nullptr;
    a->r = nullptr;
    return kek;
}

Node* next(Node* &a, int v){
    if(a==nullptr)
        return a;
    Node* kek = find(a, v);
    if(kek==nullptr)
        return get_min(a);
    a = splay(kek);
    return get_min(a->r);
}

Node* prev(Node* &a, int v){
    if(a==nullptr)
        return nullptr;
    Node* kek = find(a, v);
    if(kek==nullptr||(kek->v)<v)
        return kek;
    a = splay(kek);
    return get_max(a->l);
}

Node* insert(Node* a, int v){
    Node* kek = find(a, v);
    Node* jo = new Node(v);
    if(kek!=nullptr&&kek->v==v)
        return a;
    pair<Node*, Node*> kek1 = split(a, v);
    Node* joj = merge(kek1.first, jo);
    Node* jojo = merge(joj, kek1.second);
    return jojo;
}

Node* del(Node* a, int v){
    pair<Node*, Node*> it = split(a, v);
    auto it1 = split(it.first, v-1);
    return merge(it1.first, it.second);
}

bool exist(Node* a, int v){
    Node* kek = find(a, v);
    return kek!=nullptr&&(kek->v)==v;
}
