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

const int MAXN = 100005;
vector<int> G[2*MAXN];
int dfsnum[2*MAXN];
int low[2*MAXN];
int comp[2*MAXN];
bool inS[2*MAXN];
stack<int> S;
stack<int> sol;
int num, ncomp;

int N, M;
int target;
bool pathfound;
int p[2*MAXN];
int pos[MAXN];

void obtain_cycle( stack<int> &walk ){
	deque<int> temp;
	int m = 0;
	int u, v;
	while ( !walk.empty() ){
		u = walk.top(); walk.pop();
		if ( pos[u] == -1 ){
			pos[u] = m++;
			temp.push_back(u);
		}
		else {
			if ( (m - pos[u]) & 1 ){ // odd cycle
				while ( temp.back() != u ) {
					sol.push( temp.back() );
					temp.pop_back();
				}
				sol.push(u);
				return;
			}
			else {
				while ( temp.back() != u ) {
					pos[ temp.back() ] = -1;
					temp.pop_back();
				}
				m = pos[u] + 1;
			}
		}
	}
}

void scc( int u ){
	dfsnum[u] = low[u] = num++;
	S.push(u);
	inS[u] = true;

	int v;

	for ( int i=0; i < (int)G[u].size(); ++i ){
		v = G[u][i];
		if ( dfsnum[v] == -1 ){
			scc(v);
			low[u] = min( low[v], low[u] );
		}
		else if ( inS[v] ){
			low[u] = min( low[u], dfsnum[v] );
		}
	}
	if ( low[u] == dfsnum[u] ){
		do { 
			v = S.top();
			S.pop();
			inS[v] = false;
			comp[v] = ncomp;
		}
		while ( v != u );
		ncomp++;
	}
}

void dfs( int u ){
	if ( u == target ){ 
		pathfound = true; 
		return;
	}
	int v;
	for ( int i=0; i < (int)G[u].size() && !pathfound; ++i  ){
		v = G[u][i];
		if ( p[v] == -1 ){
			p[v] = u;
			dfs( v );	
		}
	}
}

int main(){
	int runs;
	int u, v;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			G[u].push_back( v + N );
			G[u+N].push_back( v );
		}

		num = ncomp = 0;
		fill( dfsnum, dfsnum + 2*N, -1 );
		fill( comp, comp + 2*N, -1 );
		fill( p, p + 2*N, -1 );
		fill( pos, pos + N, -1 );
		bool found = false;
		stack<int> walk;
		for ( int i=0; i < N && !found; ++i ){
			if ( dfsnum[i] == -1 ){
				scc( i );
			}
			if ( comp[i] == comp[i+N] ){ // Solution found
				found = true;
				target = i + N;
				pathfound = false;
				p[i] = i;
				dfs( i );
				u = i + N;
				while ( u != i ){
					if ( u >= N )
						walk.push( u - N );
					else 
						walk.push( u );
				
					u = p[u];
				}
				walk.push(i);
				obtain_cycle(walk);
			}
		}
		
		if ( !found ) puts("-1");
		else {
			puts("1");
			printf("%d\n", (int)sol.size());
			while ( !sol.empty() ){
				printf("%d\n", sol.top() + 1);
				sol.pop();
			}
		}
		if ( runs ){
			for ( int i=0; i < 2*N; ++i ){
				G[i].clear();
				inS[i] = false;
			}
			while ( !S.empty() ) S.pop();
			while ( !walk.empty() ) walk.pop();
		}
	}

	return 0;
}

