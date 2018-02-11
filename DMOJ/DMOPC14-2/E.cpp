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
#include <cassert>

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

const int MAXN = 1000005;	
vector<int> G[MAXN];
double p[MAXN];

int main(){
	int N, M;
	int u, v;
	scanf("%d %d", &N, &M);
	
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[u].push_back( v );
	}
	p[0] = 1.0;
	int S;
	for ( int i=1; i < N; ++i ) p[i] = 0.0;
	for ( u=0; u < N; u++ ){
		S = (int) G[u].size();
		if ( S == 0 && u > 0 ) printf("%.12lf\n", p[u]);
		for ( int j=0; j < S; ++j ){
			v = G[u][j];
			p[v] += p[u] / (long double)S;
		}
	}
	return 0;
}
