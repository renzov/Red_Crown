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

const int MAXM = 500005;
bool state[MAXM];
int G[MAXM][2];
int indeg[ MAXM ];
long long ways[ MAXM ];

int main(){
	int M;
	int u, v;
	char ini;
	long long N;

	while ( scanf("%lld %d", &N, &M) != EOF ){
		for ( int i=0; i <= M; ++i ){
			indeg[i] = 0;
			ways[i] = 0;
		}
		for ( int i=1; i <= M; ++i ){
			scanf(" %c %d %d", &ini, &u, &v);
			if ( ini == 'L' ) state[i] = false;
			else state[i] = true;
			G[i][0] = u; G[i][1] = v;
			indeg[ u ]++, indeg[ v ]++;
		}
		queue<int> q;
		bool val;
		int idx;
		ways[ 1 ] = N;
		for ( int i=1; i <= M; ++i ) if ( indeg[i]==0 ) q.push(i);
		while ( !q.empty() ){
			u = q.front();
			q.pop();
			if ( u != 0 ){	
				idx = state[u] ? 1:0;
				v = G[ u ][ idx ];
				ways[v] += ((ways[u] + 1)>>1);
				v = G[u][ 1 - idx ];
				ways[v] += (ways[u]>>1);

				v = G[u][0]; indeg[v]--; 
				if ( indeg[v] == 0 ) q.push(v);
				v = G[u][1]; indeg[v]--;
				if ( indeg[v] == 0 ) q.push(v);
			}
			val = ( ways[u]&1 )? true:false;
			state[ u ] ^= val;
		}
		for ( int i=1; i <= M; ++i )
			if ( state[i] ) putchar('R');
			else putchar('L');
		puts("");
	}
	return 0;
}

