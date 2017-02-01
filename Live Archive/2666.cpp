// INPUT description is wrong it begins with number of test cases.
// OUTPUT description is wrong. Print '\n' between testcases. 
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
#include <cassert>
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

const int MAXN = 30005;
const int MAXR = 15;

int r[MAXN];
int N;
vector<int> G[MAXN];
vector<int> C[MAXN];
int drank[MAXN][MAXR];
int D[MAXN];
int vist[MAXN];
int rmax;

int dijkstra( int s ){
	if ( r[s] == rmax ) return N;
	int cnt = 0;
	priority_queue< pii, vector<pii>, greater<pii> > q;
	q.push( pii( 0 , s ) );
	D[s] = 0;
	int rank = r[s];
	int u,v,w;

	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( w > D[u] ) continue;
		vist[ cnt++ ] = u;
		for ( int i=0; i < (int)G[u].size() ; ++i ){
			v = G[u][i];
			if ( (drank[v][rank] > w + C[u][i]) && (D[v] > w + C[u][i]) ){
				D[v] = w + C[u][i];
				q.push( pii(D[v] , v ) );
			}
		}
	}
	for ( int i=0; i < cnt; i++ ){ 
		D[ vist[i] ] = INT_MAX;
	}
	return cnt;
}

void find_drank( int rank ){
	priority_queue< pii, vector<pii>, greater<pii> > q;
	for ( int i=0; i < N; ++i ) 
		if ( r[i] >  rank ){
			drank[i][rank] = 0;
			q.push( pii( 0 , i ) );
		}

	int u,v,w;	
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( w > drank[u][rank] ) continue;
		for ( int i=0; i < (int)G[u].size() ; ++i ){
			v = G[u][i];
			if ( drank[v][rank] > w + C[u][i] ){
				drank[v][rank] = w + C[u][i];
				q.push( pii( drank[v][rank] , v ) );
			}
		}
	}
}

int main(){
	int M;
	int runs;
	int res;
	int u,v,w;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		rmax = 0;
		for ( int i=0; i < N ; ++i ){
			scanf("%d", r + i );
			if ( rmax < r[i] ) rmax = r[i];
			G[i].clear(); C[i].clear();
			D[i] = INT_MAX;
			fill( drank[i] , drank[i] + MAXR , INT_MAX );
		}
		while ( M-- ){
			scanf("%d %d %d", &u, &v, &w);
			u--,v--;
			G[u].push_back(v), C[u].push_back(w);
			G[v].push_back(u), C[v].push_back(w);
		}
		for ( int i=1; i < rmax; ++i ){
			find_drank( i );
		}
		res = 0;
		for ( int i=0; i < N; ++i ){
			res += dijkstra( i );
		}
		printf("%d\n", res);
		if (runs) putchar('\n');
	}
	return 0;
}

