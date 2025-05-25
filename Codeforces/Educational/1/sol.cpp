#include <bits/stdc++.h>
using namespace std;
 
#ifdef DEBUG
#include "../Library/debug.h"
#else
#define dbg(x...)
// #define cin fin
// #define cout fout
// const string FILE_NAME = ""; ifstream fin(FILE_NAME + ".in"); ofstream fout(FILE_NAME + ".out");
#endif
 
typedef long long ll;
// typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
// typedef vector<pl> vpl; 
 
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) for (int i = 0; i < (a); ++i)
// #define FORd(i, a, b) for (int i = (b) - 1; i >= (a); --i)
// #define F0rd(i, a) for (int i = (a) - 1; i >= 0; --i)
#define trav(a, x) for (auto& a : x)
#define f first 
#define s second
#define pb push_back
// #define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
const char nl = '\n';
const int INF = 1e9;
const int MOD = 1e9 + 7;

using T = long double;
ostream& operator<<(ostream& b, pair<T, T> a){
    b << "(" << a.f << "," << a.s << ")";
    return b;
}

T cross(pair<T, T> a, pair<T, T> b){
    return a.f * b.s - a.s * b.f;
}

int sig(T x){
    return (x > 0) - (x < 0);
}

T dot(pair<T, T> a, pair<T, T> b){
    return a.f * b.f + a.s * b.s;
}


pair<T, T> intersection(pair<T, T> a, pair<T, T> b, pair<T, T> c, pair<T, T> d){
    b.f -= a.f; b.s -= a.s;
    d.f -= c.f; d.s -= c.s;
    /* cout << "\e[91m" << nl; */
    /* cout << a << " " << b << " " << c << " " << d << nl; */
    /* cout << cross(b, d) << nl; */
    /* cout << "\e[39m" << nl; */
    T t = cross({c.f - a.f, c.s - a.s}, d) / cross(b, d);
    return {a.f + t * b.f, a.s + t * b.s};
}
 
void solve(){
    int n, m;
    cin >> n >> m;
    vector<pair<T, T>> p(n);
    for(int i = 0; i < n; ++i){
        cin >> p[i].f >> p[i].s;
    }
    T area = 0;
    for(int i = 0; i < n; ++i){
        int j = (i + 1) % n;
        area += cross(p[i], p[j]);
    }
    if(area < 0) reverse(all(p));
    F0R(_, m){
        pair<T, T> a, b;
        cin >> a.f >> a.s >> b.f >> b.s;
        vi side(n);
        T ans = 0;
        for(int i = 0; i < n; ++i) side[i] = cross({p[i].f - a.f, p[i].s - a.s}, {b.f - a.f, b.s - a.s}) >= 0;
        for(int i = 0; i < n; ++i){
            int j = (i + 1) % n;
            if(side[i] != side[j]){
                T sign = sig(cross({p[i].f - p[j].f, p[i].s - p[j].s}, {b.f - a.f, b.s - a.s}));
                /* cout << p[i] << " " << p[j] << " " << sign << nl; */
                /* pair<T, T> x = intersection(a, b, p[i], p[j]); */
                /* cout << x.f << " " << x.s << nl; */
                /* cout << i << " " << j << nl; */
                ans += sign * dot({b.f - a.f, b.s - a.s}, intersection(a, b, p[i], p[j]));
                /* cout << "-----" << ans << nl; */
            }
            if(cross({p[i].f - a.f, p[i].s - a.s}, {b.f - a.f, b.s - a.s}) == 0 && cross({p[j].f - a.f, p[j].s - a.s}, {b.f - a.f, b.s - a.s}) == 0 && dot({p[i].f - p[j].f, p[i].s - p[j].s}, {b.f - a.f, b.s - a.s}) > 0){
                /* cout << "---------------"<< nl; */
                ans += dot({p[i].f - p[j].f, p[i].s - p[j].s}, {b.f - a.f, b.s - a.s});
            }
        }
        pair<T, T> c = {b.f - a.f, b.s - a.s};
        cout << fixed << setprecision(15) << ans / sqrt((c.f * c.f + c.s * c.s)) << nl;
    }
}
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int TC = 1;
    // cin >> TC;
    while(TC--){
        solve();
    }
    return 0;
}


