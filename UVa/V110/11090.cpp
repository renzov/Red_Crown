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
const double EPS = 10e-8;
const int MAXN = 55;
const double INF = 10e8;
const char WHITE = 0;
const char GRAY = 1;
const char BLACK = 2;

bool cycle;
vector<int> G[MAXN];
vector<int> C[MAXN];
double y[MAXN];
int phi[MAXN];
bool in[MAXN];
int N;
char color[MAXN];

bool bellman_ford( double &W ){
	queue<int> q;
	for ( int i=0; i < N; ++i ){
		phi[i] = 1;
		y[i] = 0.0;
		q.push(i);
		in[i] = true;
	}
	int u , v;
	double w;
	while ( !q.empty() ){
		u = q.front(); q.pop(); in[u] = false;
		for ( int i=0; i < G[u].size(); i++ ){
			v = G[u][i];
			w = C[u][i] - W;
			if ( (y[u] + w + EPS) < y[v] ){
				y[v] = y[u] + w;
				if ( !in[v] ){
					in[v] = true; q.push(v);
					phi[v]++;
					if ( phi[v] >= N ) return false;
				}
			}
		}
	}
	return true;
}

void dfs( int u ){
	int v;
	color[u] = GRAY;
	for ( int i=0; i < G[u].size() && !cycle; ++i ){
		v = G[u][i];
		if ( color[v] == WHITE ) dfs( v );
		else if ( color[v] == GRAY ) cycle = true;
	}
	color[u] = BLACK;
}

void init(){
	for ( int i=0; i < N; ++i ){
		G[i].clear(); C[i].clear();
		color[i] = WHITE;
	}
}

int main(){
	int M;
	int runs;
	int cases = 0;
	double d;
	int u,v,w;

	scanf("%d",&runs);
	while ( runs-- ){
		cases++;
		printf("Case #%d: ",cases);
		scanf("%d %d",&N,&M);
		
		init();
		
		d = -INF;

		while ( M-- ){
			scanf("%d %d %d",&u,&v,&w);
			u--,v--;
			d = max( d , (double)w );
			G[u].push_back(v);
			C[u].push_back(w);
		}
		
		cycle = false;

		for ( int i=0; i < N && ! cycle ; ++i )
			if ( color[i] == WHITE ) dfs(i);
		
		if ( !cycle ){
			puts("No cycle found.");
			continue;
		}

		//Binary search
		double l = 0.0;
		double r = d + 1;
		double m;
	
		while ( (r - l) > 0.001 ){
			m = ( l + r ) / 2.0;
			if ( bellman_ford( m ) ){ // No negative weight cycle
				l = m;
			}
			else {
				r = m;
			}
		}
		printf("%0.2lf\n",l);
	}
	return 0;
}

