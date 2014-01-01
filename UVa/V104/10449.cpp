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

const int MAXN = 205;
const int INF = 1 << 29;

int N;
int b[MAXN];
int y[MAXN];
int phi[MAXN];
bool in[MAXN];

vector<int> G[MAXN];
vector<int> C[MAXN];

void bellman_ford(){
	
	fill( in , in + (N + 1) , false );
	fill( y  , y + (N + 1) , INF );
	fill( phi , phi + (N + 1), 0 );

	y[1] = 0;

	queue<int> q;
	
	q.push( 1 );
	phi[1]++;
	in[1] = true;
	
	int u,v,w;

	while ( !q.empty() ){
			
		u = q.front(); q.pop(); in[u] = false;
			
		if ( phi[u] >= N ) y[u] = -INF;

		for ( int j=0; j < G[u].size() ; ++j ){
			
			v = G[u][j];
			w = C[u][j];

			if ( y[v] <= -INF ) continue;
				
			if ( (y[u] + w) < y[v] ){
				
				if ( y[u] == -INF ) y[v] = -INF;
				else y[v] = y[u] + w;
				
				if ( !in[v] ){
					in[v] = true;
					phi[v]++;
					q.push( v );
				}
			}
		}
	}

}

void init(){
	for ( int i=1; i <= N ;i++ ){
		G[i].clear(); C[i].clear();
	}
}

int main(){
	int M;
	int c;
	int runs = 0;
	int u,v;

	while ( scanf("%d",&N) == 1 ){
		
		runs++;

		for ( int i=1; i <= N ; ++i )
			scanf("%d",b+i);

		init();

		scanf("%d",&M);
		
		while ( M-- ){
			scanf("%d %d",&u,&v);
			if (u > 0 && u <= N && v > 0 && v <= N){
				c = b[v] - b[u]; 
				G[u].push_back(v);
				C[u].push_back( c*c*c );
			}
		}
		bellman_ford();
		printf("Set #%d\n",runs);
		scanf("%d",&M);
		while ( M-- ){
			scanf("%d",&v);
			if ( v < 0 || v > N ) puts("?");
			else if ( y[v] < 3 || y[v] == INF ) puts("?");
			else printf("%d\n",y[v]);
		}
	}
	return 0;
}

