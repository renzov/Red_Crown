#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 200005;

int N;
int n = 0;
map<string, int> idx;
map<int, int> topsort;
int indeg[MAXN];
vector<int> G[MAXN];
int ord[MAXN];
int L[MAXN];

int get_id( const string &x ){
	if ( idx.count(x) ) return idx[x];
	indeg[n] = 0;
	return idx[x] = n++;
}

void get_ordering(){
	queue<int> q;
	for ( int i=0; i < N; ++i ){
		if ( indeg[i] == 0 ) q.push(i);
	}
	int u, v;
	int cnt = 0;
	while ( !q.empty() ){
		u = q.front(); q.pop();
		topsort[u] = cnt++;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			indeg[v]--;
			if ( indeg[v] == 0 ) q.push(v);
		}
	}
}

int lis(int m){
	int res = 0;
	int p;
	for ( int i=0; i < m; ++i ){
		p = lower_bound( L, L + m, ord[i] ) - L;
		res = max( res , p + 1 );
		L[p] = ord[i];
	}
	return res;
}

int main(){
	int M, D;
	string A, B;
	int u, v;
	
	cin >> N >> M >> D;
	while ( M-- ){
		cin >> A >> B;
		u = get_id(A), v = get_id(B);
		G[u].push_back(v);
		indeg[v]++;
	}
	get_ordering();
	int m = 0;
	for ( int i=0; i < N; ++i ){
		cin >> A;
		u = get_id(A);
		if ( topsort.count(u) )
			ord[m++] = topsort[u];
	}
	fill( L, L + m, INT_MAX );
	cout <<  2*( N - lis(m) ) << endl;
	return 0;
}

