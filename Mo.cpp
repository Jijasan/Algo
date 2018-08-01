#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

struct Q{
    int a, b, it;
    Q(){
        a = 0;
        b = 0;
        it = -1;
    }

    Q(int a, int b, int it):a(a), b(b), it(it){}
};

vector<int> c;
int a = 0, b = -1, k;
vector<int> m;
vector<int> ans;

bool kek(Q a, Q b){
    if(a.a/k!=b.a/k)
        return a.a<b.a;
    return a.b<b.b;
}

int cnt = 0;

void process(vector<Q> d){
    sort(d.begin(), d.end(), kek);
    for(int i = 0; i<d.size(); i++){
        while(a<d[i].a){
            m[c[a]]--;
            if(m[c[a]]==0)
                cnt--;
            a++;
            //cout << a << ':' << b << ' ' << cnt  << endl;
        }
        while(a>d[i].a){
            a--;
            if(m[c[a]]==0)
                cnt++;
            m[c[a]]++;
            //cout << a << ':' << b << ' ' << cnt  << endl;
        }
        while(b<d[i].b){
            b++;
            if(m[c[b]]==0)
                cnt++;
            m[c[b]]++;
            //cout << a << ':' << b << ' ' << cnt  << endl;
        }
        while(b>d[i].b){
            m[c[b]]--;
            if(m[c[b]]==0)
                cnt--;
            b--;
            //cout << a << ':' << b << ' ' << cnt  << endl;
        }
        ans[d[i].it] = cnt;
        /*cout << d[i].it << ' ' << m.size() << endl;
        for(auto it = m.begin(); it!=m.end(); it++)
            cout << it->first << ':' << it->second << ' ';
        cout << endl;*/
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    c.resize(n);
    k = sqrt(n);
    m.resize(n);
    for(int i = 0; i<n; i++){
        cin >> c[i];
        m[i] = c[i];
    }
    sort(m.begin(), m.end());
    for(int i = 0; i<n; i++){
        int l = -1, r = n;
        while(r-l>1){
            int m1 = (l+r)/2;
            if(m[m1]>c[i])
                r = m1;
            else
                l = m1;
        }
        c[i] = l;
    }
    m.assign(n, 0);
    /*for(int i = 0; i<n; i++)
        cout << c[i] << ' ';
    cout << endl;*/
    int m;
    cin >> m;
    ans.resize(m);
    vector<Q> d(m);
    for(int i = 0; i<m; i++){
        cin >> d[i].a >> d[i].b;
        d[i].a--;
        d[i].b--;
        d[i].it = i;
    }
    process(d);
    for(int i = 0; i<m; i++)
        cout << ans[i] << '\n';

    return 0;
}
