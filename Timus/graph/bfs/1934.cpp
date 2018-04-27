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
const double EPS = 1e-6;
int N;
vector<int> G[MAXN];
vector<double> P[MAXN];
int d[MAXN];
int ord[MAXN];
int pred[MAXN];
double best[MAXN];

void bfs(const int &s){
	fill( d, d + N, -1 );
	queue<int> q;
	d[s] = 0;
	q.push(s);
	int u, v;
	int n = 0;
	while ( !q.empty() ){
		u = q.front(); q.pop();
		ord[n++] = u;
		for ( int i=0; i < (int) G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				q.push( v );
			}
		}
	}
}

void print(const int &s, const int &u){
	if ( u == s ){ printf("%d", u + 1); return; }
	print( s, pred[u] );
	printf(" %d", u + 1);
}

int great( const double &A, const double &B ){
	return fabs(A-B) > EPS && A > B;
}

int main(){
	int M;
	int u, v, w;
	int s, t;
	double p;
	scanf("%d %d %d %d", &N, &M, &s, &t);
	s--, t--;

	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		u--, v--;
		G[u].push_back(v); P[u].push_back( (double)w/100.0 );
		G[v].push_back(u); P[v].push_back( (double)w/100.0 );
	}
	bfs(s);
	best[s] = 1.0;
	for ( int i=1; i < N; ++i ){
		u = ord[i];
		best[u] = 1.0;
		for ( int i=0; i < (int)G[u].size(); ++i ){
			v = G[u][i], p = P[u][i];
			if ( d[u] - d[v] == 1  ){
				if ( great( best[u], best[v]*p ) > 0 )
				best[u] = best[v]*p;
				pred[u] = v;
			}
		}
	}
	printf("%d %.7f\n", d[t] + 1, best[t]);
	print(s, t);
	puts("");
	return 0;
}

