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
typedef pair< int , pii > piii;

const int MAXE = 3005;
const int MAXV = 2005;

piii E[MAXE];
int p[MAXV];
int R[MAXV];

inline void make_set( int x ){ p[x] = x; }
inline int find_set( int x ){ return (x == p[x])? x:(p[x] = find_set(p[x])); }
bool link( int u, int v ){
	if ( (u=find_set(u)) == (v=find_set(v)) ) return false;
	if ( R[u] > R[v] ){
		p[v] = u;
	}
	else if ( R[v] > R[u] ){ 
		p[u] = v;
	}
	else {
		p[v] = u, R[u]++;
	}
	return true;
}

int main(){
	int N, M, k;
	int cnt;
	int res;
	int runs;
	int s,e;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d %d", &N, &M, &s, &e);
		for ( int i=0; i < M; ++i ){
			scanf("%d %d %d", &E[i].second.first, &E[i].second.second, &E[i].first);
		}
		res = INT_MAX;
		sort( E , E + M );
		for ( int j=0; j < M; ++j ){
		
			for ( int i=0; i < N; ++i ) make_set(i);

			for ( k=j; find_set(s) != find_set(e) && k < M; ++k ){
				link( E[k].second.first, E[k].second.second );
			}
			if ( find_set(s) == find_set(e) )
				res = min( res , E[k-1].first - E[j].first );

		}
		if ( res < INT_MAX ) printf("%d\n", res);
		else puts("NO PATH");
	}
	return 0;
}


