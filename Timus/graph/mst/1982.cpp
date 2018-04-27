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
#include <numeric>

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
typedef pair< int, pii > edge;

const int MAXN = 128;
int p[MAXN];

edge E[MAXN * MAXN];
int e = 0;

inline int find_set( const int &x ){
	return ( x == p[x] )? x:( p[x] = find_set(p[x]) );
}

void union_set( int u, int v){
	if ( u != v ){ 
		p[v] = u;
	}
}

int main(){
	int u, v, w;
	int N, K;

	cin >> N >> K;
	for ( int i=0; i < N; ++i ) p[i] = i;
	for ( int i=0; i < K; ++i ){
		cin >> v;
		v--;
		if ( i ){
			union_set( find_set(u), find_set(v) );
		}
		u = v;
	}
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < N; ++j ){
			cin >> w;
			if ( i < j ) E[e++] = edge( w, pii(i,j) );
		}
	}
	sort( E, E + e );
	int res = 0;
	for ( int i=0; i < e; ++i ){
		u = E[i].second.first;
		v = E[i].second.second;
		u = find_set(u), v = find_set(v);
		if ( u != v ){
			res += E[i].first;
			union_set(u, v);
		}
	}
	cout << res << endl;
	return 0;
}

