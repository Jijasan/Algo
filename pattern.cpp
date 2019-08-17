#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <deque>
#include <ctime>
#include <cmath>
#include <stack>
#include <set>
#include <map>

using namespace std;

const int INF = 1000000007;

struct Graph{
    int m = 0;
    bool undirected = true;
    vector<vector<int> > g;

    Graph(){}

    Graph(bool direc){
        undirected = !direc;
    }

    void resize(int n, int _m){
        g.resize(n);
        m = _m;
    }

    vector<int>& operator[](int it){
        return g[it];
    }

    int size(){
        return g.size();
    }

    void build(vector<int> p){
        int n = p.size()+1;
        resize(n, n-1);
        for(int i = 1; i<n; i++){
            int a = i, b = p[a-1];
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }
};

template<typename T>
struct Segment_Tree{
    int n = 0, log;
    T def;
    T (*func)(T a, T b);
    vector<T> tr;

    Segment_Tree(){}

    Segment_Tree(T (*f)(T a, T b), T defl){
        func = f;
        def = defl;
    }

    int& operator[](int it){
        return tr[it];
    }

    void setdef(T a){
        def = a;
    }

    void resize(int _n){
        int it = 1;
        n = _n;
        while(_n){
            _n >>= 1;
            it++;
        }
        if(4*n==(1<<it))
            it--;
        log = it;
        tr.resize(1<<it, def);
    }

    void build(int l, int r, int it, vector<T> &a){
        if(l+1==r){
            tr[it] = a[l];
            return;
        }
        int m = (l+r)/2;
        build(l, m, 2*it, a);
        build(m, r, 2*it+1, a);
        tr[it] = func(tr[2*it], tr[2*it+1]);
    }

    void build(vector<T> &a){
        build(0, n, 1, a);
    }

    T get(int l, int r, int x, int y, int it){
        if(y<=l||r<=x||r<=l)
            return def;
        if(x<=l&&r<=y)
            return tr[it];
        int m = (l+r)/2;
        return func(get(l, m, x, y, 2*it), get(m, r, x, y, 2*it+1));
    }

    T get(int l, int r){
        return get(0, n, l, r, 1);
    }

    void upd(int l, int r, int x, T y, int it){
        if(r<=x||x<l||r<=l)
            return;
        if(l+1==r){
            tr[it] = y;
            return;
        }
        int m = (l+r)/2;
        upd(l, m, x, y, 2*it);
        upd(m, r, x, y, 2*it+1);
        tr[it] = func(tr[2*it], tr[2*it+1]);
    }

    void fupd(int l, int r, int x, T y, int it){
        if(r<=x||x<l||r<=l)
            return;
        if(l+1==r){
            tr[it] = func(tr[it], y);
            return;
        }
        int m = (l+r)/2;
        fupd(l, m, x, y, 2*it);
        fupd(m, r, x, y, 2*it+1);
        tr[it] = func(tr[2*it], tr[2*it+1]);
    }

    void upd(int it, T k){
        upd(0, n, it, k, 1);
    }

    void fupd(int it, T k){
        fupd(0, n, it, k, 1);
    }
};

template<typename T>
struct Treap{
    T x;
    int y = rand(), sz = 1, it = 1, h = 1;
    Treap *l = nullptr, *r = nullptr, *p = nullptr;

    Treap(){}

    Treap(T a){
        x = a;
    }

    T& operator[](int I){
        if(I==it)
            return x;
        if(I<it)
            return (*l)[I];
        return (*r)[I-it];
    }
};

template<typename T>
struct Fenwick_Tree{
    int n;
    T (*pls)(T a, T b) = [&](T a, T b){return a+b;};
    T (*mns)(T a, T b) = [&](T a, T b){return a-b;};
    vector<T> tr;

    Fenwick_Tree(){}

    Fenwick_Tree(T (*p)(T a, T b), T (*m)(T a, T b)){
        pls = p;
        mns = m;
    }

    void resize(int _n){
        n = _n;
        tr.resize(n);
    }

    void build(vector<T> &a){
        tr = a;
        for(int i = 1; i<n; i++)
            tr[i] = pls(tr[i-1], tr[i]);
        for(int i = 1; i<n; i++)
            tr[i] = mns(tr[i], ((((i&(i+1))-1)<0)?0:tr[(i&(i+1))-1]));
    }

    T get(int a){
        T ans = 0;
        for(int i = a; i>=0; i = (i&(i+1))-1)
            ans = pls(ans, tr[i]);
        return ans;
    }

    T get(int l, int r){
        return mns(get(r), get(l-1));
    }

    void upd(int it, T k){
        for(int i = it; i<n; i = (i|(i+1)))
            tr[it] = pls(tr[it], k);
    }

    T& operator[](int it){
        return tr[it];
    }
};

template<typename T>
struct Matrix{
    int n = 0, m = 0;
    vector<vector<T> > a;

    Matrix(){}

    Matrix(int n, int m):n(n), m(m){
        a.resize(n, vector<T>(m));
    }

    Matrix(vector<vector<T> > _a){
        a = _a;
        n = _a.size();
        m = _a[0].size();
    }

    vector<T>& operator[](int it){
        return a[it];
    }

    void resize(int _n, int _m){
        n = _n;
        m = _m;
        a.resize(n, vector<T>(m));
    }
};

struct Edge {
    int a, b;
    long long fl, cp, cs;

    Edge() {};

    Edge(int a, int b, long long cp, long long cs):a(a), b(b), cp(cp), cs(cs){
        fl = 0;
    }

    bool isfull() const {
        return fl==cp;
    }

    bool isntfull() const {
        return !isfull();
    }

    long long freeflow() const {
        return cp-fl;
    }
};

struct Flow{
    int s, t, n;
    vector<Edge> e;
    vector<bool> u;
    vector<long long> d;
    vector<vector<int> > g;
    const long long INF = 1000000000000000007;

    long long max_flow = 0, min_cost = 0;

    void add(int a, int b, long long cp, long long cs) {
        g[a].push_back(e.size());
        e.push_back(Edge(a, b, cp, cs));
        g[b].push_back(e.size());
        e.push_back(Edge(b, a, 0, -cs));
    }

    bool bfs(){
        u.assign(n, 0);
        d.assign(n, INF);
        queue<int> q;
        q.push(s);
        u[s] = true;
        d[s] = 0;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            u[v] = false;
            for(int i = 0; i<int(g[v].size()); i++){
                int it = g[v][i];
                if(e[it].isfull())
                    continue;
                if(d[v]+e[it].cs<d[e[it].b]){
                    d[e[it].b] = d[v]+e[it].cs;
                    if(!u[e[it].b]){
                        u[e[it].b] = true;
                        q.push(e[it].b);
                    }
                }
            }
        }
        return d[t] != INF;
    }

    vector<int> lst;

    long long dfs(long long v, long long flow) {
        if (flow == 0)
            return flow;
        if (v == t)
            return flow;
        //cout << v << ':' << lst[v] << endl;
        while (lst[v] < int(g[v].size())) {
            //cout << v << endl;
            long long it = g[v][lst[v]];
            lst[v]++;
            //cout << d[e[it].b] << ' ' << d[v] << ' ' << e[it].cs << endl;
            if (d[e[it].b] - e[it].cs == d[v] && e[it].isntfull()) {
                long long flow1 = dfs(e[it].b, min(flow, e[it].freeflow()));
                //cout << v << ':' << e[it].b << endl;
                if (flow1) {
                    lst[v]--;
                    e[it].fl += flow1;
                    e[it ^ 1].fl -= flow1;
                    return flow1;
                }
            }
        }
        return 0;
    }

    Flow(){}

    Flow(vector<vector<pair<int, pair<int, int> > > > _g){
        n = _g.size();
        for(int v = 0; v<n; v++){
            for(int i = 0; i<int(_g[v].size()); i++){
                int a = _g[v][i].first, b = _g[v][i].second.first, c = _g[v][i].second.second;
                add(v, a, b, c);
            }
        }
    }

    Flow(int _n, vector<Edge> _e){
        n = _n;
        int m = _e.size();
        for(int i = 0; i<m; i++){
            add(_e[i].a, _e[i].b, _e[i].cp, _e[i].cs);
        }
    }

    void resize(){
        g.resize(n);
        u.resize(n);
        d.resize(n);
        lst.resize(n);
    }

    void calc(){
        resize();
        while (bfs()) {
            lst.assign(n, 0);
            while (true)
                if (dfs(s, INF) == 0)
                    break;
        }
        for(int i = 0; i<int(g[s].size()); i++)
            max_flow += e[g[s][i]].fl;
        for(int i = 0; i<int(e.size()); i += 2)
            min_cost += e[i].fl*e[i].cs;
    }
};

template<typename T>
Matrix<T> operator*(Matrix<T> &a, Matrix<T> &b){
    Matrix<T> c(a.n, b.m);
    for(int i = 0; i<a.n; i++){
        for(int j = 0; j<b.m; j++){
            for(int y = 0; y<a.m; y++){
                c[i][j] += a[i][y]*b[y][j];
            }
        }
    }
    return c;
}

template<typename T>
Treap<T>* merge(Treap<T>* a, Treap<T>* b){
    if(a==nullptr)
        return b;
    if(b==nullptr)
        return a;
    if((a->y)>(b->y)){
        b->p = a;
        a->sz += b->sz;
        a->r = merge(a->r, b);
        a->h = max(((a->l!=nullptr)?a->l->h:0), ((a->r!=nullptr)?a->r->h:0))+1;
        return a;
    }
    a->p = b;
    b->sz += a->sz;
    b->it += a->sz;
    b->l = merge(a, b->l);
    b->h = max(((b->l!=nullptr)?b->l->h:0), ((b->r!=nullptr)?b->r->h:0))+1;
    return b;
}

template<typename T>
pair<Treap<T>*, Treap<T>*> split(Treap<T>* a, T k){
    if(a==nullptr)
        return {nullptr, nullptr};
    if((a->x)<k){
        if(a->r!=nullptr){
            a->r->p = nullptr;
            a->sz -= a->r->sz;
        }
        auto it = split(a->r, k);
        a->r = nullptr;
        a->h = ((a->l!=nullptr)?a->l->h:0)+1;
        return {merge(a, it.first), it.second};
    }
    if(a->l!=nullptr){
        a->l->p = nullptr;
        a->sz -= a->l->sz;
        a->it -= a->l->sz;
    }
    auto it = split(a->l, k);
    a->l = nullptr;
    a->h = ((a->r!=nullptr)?a->r->h:0)+1;
    return {it.first, merge(it.second, a)};
}

template<typename T>
pair<Treap<T>*, Treap<T>*> splitk(Treap<T>* a, T k){
    if(a==nullptr)
        return {nullptr, nullptr};
    if((a->it)<k){
        if(a->r!=nullptr){
            a->r->p = nullptr;
            a->sz -= a->r->sz;
        }
        auto it = splitk(a->r, k-(a->it));
        a->r = nullptr;
        return {merge(a, it.first), it.second};
    }
    if(a->l!=nullptr){
        a->l->p = nullptr;
        a->sz -= a->l->sz;
        a->it -= a->l->sz;
    }
    auto it = splitk(a->l, k);
    a->l = nullptr;
    return {it.first, merge(it.second, a)};
}

template<typename T>
void build(vector<T> &b, Treap<T>* &a){
    int n  = b.size();
    a = nullptr;
    for(int qwe = 0; qwe<n; qwe++)
        a = merge(a, new Treap<T>(b[qwe]));
}

template<typename T>
Treap<T>* insert(Treap<T> *a, T b){
    auto it = split(a, b);
    return merge(merge(it.first, b), it.second);
}

template<typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &a);

template<typename T1, typename T2>
ostream &operator<(ostream &o, const pair<T1, T2> &a);

template<typename T>
ostream &operator<<(ostream &o, const vector<T> &a);

template<typename T>
ostream &operator<(ostream &o, const vector<T> &a);

template<typename T>
ostream& operator<<(ostream &o, const vector<vector<T> > &a);

template<typename T>
ostream& operator<<(ostream &o, const set<T> &a);

template<typename T1, typename T2>
ostream& operator<<(ostream &o, const map<T1, T2> &a);

ostream& operator<<(ostream &o, Graph &g);

template<typename T>
ostream& operator<<(ostream &o, Segment_Tree<int> &tr);

template<typename T>
ostream& operator<<(ostream &o, Treap<T> *a);

template<typename T>
ostream& operator<<(ostream &o, Fenwick_Tree<T> &a);

template<typename T>
ostream& operator<(ostream &o, Treap<T> *a);

template<typename T>
ostream& operator<<(ostream &o, Matrix<T> &a);

template<typename T1, typename T2>
ifstream& operator>>(ifstream &i, pair<T1, T2> &a);

template<typename T>
ifstream& operator>>(ifstream &i, vector<T> &a);

istream& operator>>(istream &i, Graph &g);

template<typename T>
istream& operator>>(istream &i, Segment_Tree<T> &a);

template<typename T>
istream& operator>>(istream &i, Treap<T>* &a);

template<typename T>
istream& operator>>(istream &i, Fenwick_Tree<T> &tr);

template<typename T>
istream& operator>>(istream &i, Matrix<T> &a);

istream& operator>>(istream &i, Flow &F);

istream& operator>(istream &i, Flow &F);

template<typename T>
string to_str(T a){
    stringstream ss;
    string s;
    ss << a;
    getline(ss, s);
    return s;
}

template<typename T1, typename T2>
ostream &operator<(ostream &o, const pair<T1, T2> &a) {
    o << '(' << a.first << ", " << a.second << ')';
    return o;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &a) {
    o << a.first << ' ' << a.second;
    return o;
}

template<typename T>
ostream &operator<<(ostream &o, const vector<T> &a) {
    int n = a.size();
    o << '{';
    for (int i = 0; i < n; i++) {
        o << a[i];
        if (i + 1 < n)
            o << ", ";
    }
    o << '}';
    return o;
}

template<typename T>
ostream &operator<(ostream &o, const vector<T> &a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        o << a[i];
        if (i + 1 < n)
            o << ' ';
    }
    return o;
}

template<typename T>
ostream& operator<<(ostream &o, const vector<vector<T> > &a){
    int n = a.size(), n1 = n;
    long long it = 1;
    while(n1){
        it *= 10;
        n1 /= 10;
    }
    it /= 10;
    for(int i = 0; i<n; i++){
        int it1 = it;
        while(it1>max(i, 1)){
            o << ' ';
            it1 /= 10;
        }
        o << i << ") " << a[i];
        if(i+1<n)
            o << '\n';
    }
    return o;
}

template<typename T>
ostream& operator<<(ostream &o, const set<T> &a){
    o << '(';
    for(auto it = a.begin(); it!=a.end(); it++){
        if(it!=a.begin())
            o << " < ";
        o << *it;
    }
    o << ')';
    return o;
}

template<typename T1, typename T2>
ostream& operator<<(ostream &o, const map<T1, T2> &a){
    o << '(';
    for(auto it = a.begin(); it!=a.end(); it++){
        if(it!=a.begin())
            o << "  ";
        o << it->first << ':' << it->second;
    }
    o << ')';
    return o;
}

ostream& operator<<(ostream &o, Graph &g){
    for(int i = 0; i<int(g.size()); i++){
        o << i << ") ";
        for(int j = 0; j<int(g[i].size()); j++)
            o << g[i][j] << ' ';
        o << '\n';
    }
    return o;
}

void printST(int l, int r, int it, int log, vector<vector<int> > &a, Segment_Tree<int> &tr){
    a[log].push_back(tr[it]);
    if(l+1==r){
        if(log+1!=tr.log){
            a[log+1].push_back(INF);
            a[log+1].push_back(INF);
        }
        return;
    }
    int m = (l+r)/2;
    printST(l, m, 2*it, log+1, a, tr);
    printST(m, r, 2*it+1, log+1, a, tr);
}

template<typename T>
int len(T a){
    stringstream ss;
    ss << a;
    string s;
    getline(ss, s);
    return s.size();
}

ostream& operator<<(ostream &o, Segment_Tree<int> &tr){
    vector<vector<int> > a(tr.log);
    printST(0, tr.n, 1, 0, a, tr);
    vector<vector<int> > sz(tr.log);
    for(int i = 0; i<int(a[tr.log-1].size()); i++)
        sz[tr.log-1].push_back((a[tr.log-1][i]==INF)?0:len(a[tr.log-1][i]));
    for(int i = tr.log-2; i>=0; i--){
        for(int j = 0; j<int(a[i].size()); j++){
            int ln = len(a[i][j]);
            sz[i].push_back(max(ln, sz[i+1][2*j]+sz[i+1][2*j+1]+1));
            int it = 2*j;
            while(sz[i][j]>sz[i+1][2*j]+sz[i+1][2*j+1]+1){
                sz[i+1][it]++;
                it ^= 1;
            }
        }
    }
    vector<bool> u(sz[0][0]+2);
    for(int i = 0; i<tr.log; i++){
        for(int j = 0; j<sz[0][0]+2; j++)
            o << '-';
        o << '\n';
        int it = 0;
        for(int j = 0; j<int(sz[i].size()); j++){
            if(a[i][j]!=INF||(j&&a[i][j-1]!=INF)){
                o << '|';
                if(i+1==tr.log)
                    u[it++] = true;
            }
            else{
                o << ' ';
                it++;
            }
            int vd = sz[i][j]-((a[i][j]==INF)?0:len(a[i][j]));
            for(int y = 0; y<(vd/2); y++)
                o << ' ';
            if(a[i][j]!=INF){
                o << a[i][j];
                if(i+1==tr.log)
                    for(int qwe = 0; qwe<sz[i][j]; qwe++)
                        u[it++] = true;
            }
            else
                it += sz[i][j];
            for(int y = 0; y<((vd+1)/2); y++)
                o << ' ';
        }
        if(i+1==tr.log)
            u[it] = true;
        o << '|';
        o << '\n';
    }
    for(int i = 0; i<sz[0][0]+2; i++){
        if(u[i])
            o << '-';
        else
            o << ' ';
    }
    return o;
}

template<typename T>
ostream& operator<<(ostream &o, Treap<T> *a){
    if(a==nullptr)
        return o;
    o << a->l << a->x << ' ' << a->r;
    return o;
}

template<typename T>
int print(Treap<T> *a, vector<string> &s, int it){
    if(a==nullptr)
        return 0;
    int ln = len(a->x);
    for(int i = 0; i<ln+2; i++)
        s[it].push_back('-');
    s[it+1].push_back('|');
    stringstream ss;
    ss << (a->x);
    string t;
    getline(ss, t);
    for(int i = 0; i<int(t.size()); i++)
        s[it+1].push_back(t[i]);
    s[it+1].push_back('|');
    for(int i = 0; i<ln+2; i++)
        s[it+2].push_back('-');
    if(a->l==nullptr&&a->r==nullptr){
        for(int i = 0; i<3; i++)
            s[it+i].push_back(' ');
        for(int j = it+3; j<int(s.size()); j++)
            while(s[j].size()<s[it+2].size())
                s[j].push_back(' ');
        return ln+3;
    }
    int ln1 = 0, ln2 = 0;
    if(a->l!=nullptr){
        s[it+3].push_back('|');
        s[it+4].push_back('|');
        ln1 = print(a->l, s, it+5);
        while(s[it].size()<s[it+5].size())
            s[it].push_back(' ');
    }
    if(a->r!=nullptr){
        s[it+3].push_back(' ');
        s[it+4].push_back(' ');
        s[it+3].push_back('\\');
        while(s[it+4].size()<s[it+5].size())
            s[it+4].push_back(' ');
        while(s[it+3].size()<s[it+4].size())
            s[it+3].push_back('_');
        if(a->l==nullptr)
            s[it+4].push_back(' ');
        s[it+4].push_back('\\');
        for(int j = it+5; j<int(s.size()); j++)
            while(s[j].size()<s[it+4].size())
                s[j].push_back(' ');
        print(a->r, s, it+5);
        while(s[it].size()<s[it+5].size())
            s[it].push_back(' ');
    }
    s[it].push_back(' ');
    for(int j = it+1; j<int(s.size()); j++)
        while(s[j].size()<s[it].size())
            s[j].push_back(' ');
    ln = max(ln, ln1+ln2);
    ln++;
    return ln;
}

template<typename T>
ostream& operator<(ostream &o, Treap<T> *a){ /// Another output format for Treap<int> as ASCII Art Tree
    vector<string> s((a->h)*5-2);
    print(a, s, 0);
    for(int i = 0; i<int(s.size()); i++)
        o << s[i] << '\n';
    return o;
}

template<typename T>
ostream& operator<<(ostream &o, Fenwick_Tree<T> &tr){
    o << '[';
    for(int i = 0; i<tr.n; i++){
        if(i==0)
            o << ':';
        o << tr[i];
    }
    o << ']';
    return o;
}

int print(vector<string> &s, Graph &g, int v, int it, vector<bool> &u){
    u[v] = true;
    while(int(s.size())<=it){
        s.push_back("");
        while(s.size()>1&&s[s.size()-2].size()>s.back().size())
            s.back().push_back(' ');
    }
    s[it] += to_str(v);
    int ln = len(v);
    bool kek = false;
    for(int i = 0; i<int(g[v].size()); i++)
        kek |= !u[g[v][i]];
    if(kek){
        while(int(s.size())<=it+2){
            s.push_back("");
            while(s.size()>1&&s[s.size()-2].size()>s.back().size())
                s.back().push_back(' ');
        }
        for(int i = it+1; i<int(s.size()); i++)
            while(s[i].size()<s[it].size())
                s[i].push_back(' ');
        s[it+1].push_back('\\');
        s[it+2].push_back(' ');
        int ln1 = 0;
        for(int i = 0; i<int(g[v].size()); i++){
            if(u[g[v][i]])
                continue;
            for(int j = 0; j<ln1; j++){
                s[it+1].push_back('_');
                if(j)
                    s[it+2].push_back(' ');
            }
            s[it+2].push_back('\\');
            for(int j = it+3; j<int(s.size()); j++)
                while(s[j].size()<s[it+2].size())
                    s[j].push_back(' ');
            ln1 = print(s, g, g[v][i], it+3, u)+1;
            ln += ln1;
        }
    }
    return ln;
}

ostream& operator<(ostream &o, Graph &g){ /// ASCII Art of DFS-Tree of Graph
    vector<string> s;
    vector<bool> u(g.size());
    print(s, g, 0, 0, u);
    for(int i = 0; i<int(s.size()); i++)
        o << s[i] << '\n';
    return o;
}

template<typename T>
ostream& operator<<(ostream &o, Matrix<T> a){
    vector<string> s(a.n+2);
    s[0].push_back('-');
    s[a.n+1].push_back('-');
    s[0].push_back('-');
    s[a.n+1].push_back('-');
    for(int i = 0; i<a.n; i++){
        s[i+1].push_back('|');
        s[i+1].push_back(' ');
    }
    for(int j = 0; j<a.m; j++){
        int mxx = 0;
        for(int i = 0; i<a.n; i++){
            s[i+1] += to_str(a[i][j]);
            mxx = max(mxx, int(s[i+1].size()));
        }
        for(int i = 0; i<a.n; i++){
            while(int(s[i+1].size())<mxx)
                s[i+1].push_back(' ');
            s[i+1].push_back(' ');
        }
    }
    for(int i = 3; i<int(s[1].size()); i++){
        s[0].push_back(' ');
        s[a.n+1].push_back(' ');
    }
    s[0].push_back('-');
    s[a.n+1].push_back('-');
    s[0].push_back('-');
    s[a.n+1].push_back('-');
    for(int i = 0; i<a.n; i++){
        s[i+1].push_back('|');
        s[i+1].push_back(' ');
    }
    for(int i = 0; i<a.n+2; i++)
        o << s[i] << '\n';
    return o;
}

template<typename T1, typename T2>
istream& operator>>(istream &i, pair<T1, T2> &a){
    i >> a.first >> a.second;
    return i;
}

template<typename T>
istream& operator>>(istream &i, vector<T> &a){
    int n = a.size();
    for(int j = 0; j<n; j++)
        i >> a[j];
    return i;
}

istream& operator>>(istream &i, Graph &g){
    for(int j = 0; j<g.m; j++){
        int a, b;
        i >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        if(g.undirected)
            g[b].push_back(a);
    }
    return i;
}

template<typename T>
istream& operator>>(istream &i, Segment_Tree<T> &a){
    vector<T> b(a.n);
    cin >> b;
    a.build(b);
    return i;
}

template<typename T>
istream& operator>>(istream &i, Treap<T>* &a){
    int n;
    i >> n;
    T b;
    a = nullptr;
    for(int qwe = 0; qwe<n; qwe++){
        i >> b;
        a = merge(a, new Treap<T>(b));
    }
    return i;
}

template<typename T>
istream& operator>>(istream &i, Fenwick_Tree<T> &tr){
    vector<T> a(tr.n);
    for(int j = 0; j<tr.n; j++)
        i << a[j];
    tr.build(a);
    return i;
}

template<typename T>
istream& operator>>(istream &i, Matrix<T> &a){
    for(int y = 0; y<a.n; y++)
        for(int j = 0; j<a.m; j++)
            i >> a[y][j];
    return i;
}

istream& operator>>(istream &i, Flow &F){
    i >> F.n;
    int m;
    i >> m;
    for(int j = 0; j<m; j++){
        int a, b, c, d;
        i >> a >> b >> c >> d;
        a--;
        b--;
        F.add(a, b, c, d);
    }
    F.resize();
    F.s = 0;
    F.t = F.n-1;
    return i;
}

istream& operator>(istream &i, Flow &F){
    int n;
    i >> n;
    vector<vector<int> > a(n, vector<int>(n));
    i >> a;
    F.s = 0;
    F.n = 2*n+2;
    F.t = F.n-1;
    F.resize();
    for(int i = 0; i<n; i++){
        F.add(0, i+1, 1, 0);
        F.add(n+i+1, 2*n+1, 1, 0);
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            F.add(i+1, n+j+1, 1, a[i][j]);
    return i;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Segment_Tree<int> st([](int a, int b){return a+b;}, 0);
    int n;
    cin >> n;
    st.resize(n);
    while(true){
        int t;
        cin >> t;
        if(t==0)
            break;
        if(t==1){
            int it, k;
            cin >> it >> k;
            it--;
            st.fupd(it, k);
        }
        else{
            int l, r;
            cin >> l >> r;
            l--;
            cout << st.get(l, r) << '\n';
        }
        //cout << st << endl;
    }

    return 0;
}
