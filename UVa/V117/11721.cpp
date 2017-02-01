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

const int MAXN = 1005;
const int INF = 1<<30;
int N;
vector<int> G[ MAXN ];
vector<int> C[ MAXN ];
int num[MAXN];
int low[MAXN];
bool in[MAXN];
int number;

int NSCC; 		//Number of strongly connected components
stack<int> S;

vector<int> scc[MAXN]; 	// Vertices of scc[i]
int SCI[MAXN]; 			// The reverse of scc
vector<int> neg_cycle;  //Has the scc vertices that have negative cycle
bool visited[MAXN];

int y[ MAXN ];
int phi[ MAXN ];


void init(){ 
	for ( int i=0; i < N; ++i ){ G[i].clear(); C[i].clear(); scc[i].clear(); } 
	neg_cycle.clear(); 
}

void dfs_tarjan( int u ){

	low[u] = num[u] = number++;
	S.push(u);
	in[u] = true;

	int  v;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( num[v] == -1 ){
			dfs_tarjan( v );
			low[u] = min( low[u] , low[v] );
		}
		else if (in[v]) {
			low[u] = min( low[u] , num[v] );
		}
	}
	
	if ( num[u] == low[u] ){
		do{
			v = S.top(); S.pop(); in[v] = false;
			SCI[v] = NSCC;
			scc[NSCC].push_back(v);
		}
		while ( v != u );
		NSCC++;
	}
}

bool bellman_ford( int c ,  vector<int> &V ){

	int size = V.size();

	int u , v , w;

	for ( int i=0; i < size; ++i ){
		u = V[i];
		phi[u] = 0;
		y[u] = INF;
		in[u] = false;
	}

	
	u = V[0];
	y[u] = 0;
	phi[u]++;

	queue<int> q;
	q.push( u );
	in[u] = true;

	while ( !q.empty() ){
		
		u = q.front(); q.pop(); in[u] = false;

		if ( phi[u] >= size ) return false;
		for ( int i=0; i < G[u].size() ; ++i ){
			v = G[u][i];
			w = C[u][i];
			if ( SCI[v] == c && (y[u] + w < y[v]) ){
				y[v] = y[u] + w;
				if ( !in[v] ){ q.push(v); in[v] = true; phi[v]++; }
			}
		}
	}
	return true;
}

void find_scc(){
	number = 0;
	while (!S.empty()) S.pop();
	fill( num , num + N , -1 );
	fill( in , in + N , false );
	NSCC = 0;

	for ( int i=0; i < N; ++i )
		if ( num[i] == -1 )
			dfs_tarjan(i);

	for ( int i=0; i < NSCC; ++i ){
		if ( scc[i].size() > 1 ){
			if ( !bellman_ford( i , scc[i] ) ){
				neg_cycle.push_back( i );
			}
		}
	}
}

void dfs( int u ){
	int v;
	visited[u] = true;
	for ( int i=0; i < G[u].size(); ++i ){
		v = G[u][i];
		if ( !visited[v] ) dfs( v );
	}
}

int main(){

	int runs;
	int cases = 0;
	int u,v,w;
	int M;

	scanf("%d",&runs);
	while ( runs-- ){
		cases++;
		scanf("%d %d",&N,&M);
	
		init();

		while ( M-- ){
			scanf("%d %d %d",&u,&v,&w);
			G[v].push_back( u );
			C[v].push_back( w );
		}

		find_scc();

		printf("Case %d:",cases);

		if ( neg_cycle.size() == 0 ){ puts(" impossible"); continue; }

		int comp;
		fill( visited , visited + N , false );
		for ( int i=0; i < neg_cycle.size(); ++i ){
			comp = neg_cycle[i];
			u = scc[comp][0];
			if ( !visited[ u ] ) dfs(u);
		}
		
		for ( int i=0; i < N; ++i )
			if ( visited[i] )
				printf(" %d",i);

		puts("");
	}
	return 0;
}

