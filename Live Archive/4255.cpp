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

const int MAXN = 20;

int N;
vector<int> G[MAXN];
vector<int> W[MAXN];
int d[MAXN];
bool inQ[MAXN];

void add_edge( const int &u, const int &v, const int &w ){
	G[u].push_back(v);
	W[u].push_back(w);
}

void bellman_ford( int s ){
	queue<int> q;
	fill( d, d + N + 2, INT_MAX );
	fill( inQ, inQ + N + 2, false );
	d[s] = 0;
	
	q.push(s);
	inQ[s] = true;
	int u, v, w;

	while ( !q.empty() ){ // Should finish, since there is no infeasible testcase (maybe)
		u = q.front(); q.pop();
		inQ[u] = false;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			w = W[u][i];
			if ( d[u] + w < d[v] ){ // relax
				d[v] = d[u] + w;
				if ( !inQ[v] ){
					q.push(v);
					inQ[v] = true;
				}
			}
		}
	}
}

int main(){
	int runs;
	char sgn;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		for ( int i=1; i <=N; ++i )
			for ( int j=i; j <= N; ++j ){
				scanf(" %c", &sgn);
				if ( sgn == '+' ){
					add_edge( j , i - 1, -1 );
				}
				else if ( sgn == '-' ){
					add_edge( i - 1, j , -1 );
				}
				else { // sgn == '0'
					add_edge( j , i - 1, 0 );
					add_edge( i - 1, j , 0 );					
				}
			}
		// extra constraints given in the statement
		for ( int i=1; i <= N; ++i ){
			add_edge( i-1 , i, 10 );
			add_edge( i , i - 1 , 10 );			
		}
		// adding extra vertex
		for ( int i=0; i <= N; ++i )
			add_edge( N+1, i, 0 );

		bellman_ford( N + 1 );
		// substract the constant d[0] to obtain answer
		for ( int i=1; i <= N; ++i )
			d[i] -= d[0];
		d[0] = 0;
		// print answer
		printf("%d", d[1] - d[0]);
		for  ( int i=2; i <= N; ++i ){
			printf(" %d", d[i] - d[i-1]);
		}
		puts("");
		if ( runs ){
			for ( int i=0; i < N+2; ++i )
				G[i].clear(), W[i].clear();
		}
	}
	return 0;
}

