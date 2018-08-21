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
typedef pair< long long , pii > piii;

const int MAXN = 50005;
int N;

vector<int> G1[MAXN];
vector<int> G2[MAXN];
vector<int> W1[MAXN];
long long d[2][MAXN];


int dijkstra( const int &s, const int &t ){

	priority_queue< piii, vector<piii>, greater< piii >  > q;
	for ( int i=0; i < N; ++i ) d[0][i] = d[1][i] = LLONG_MAX;
	d[0][s] = 0;

	int u, v, we, used;
	long long w;

	q.push( piii( 0 , pii( s, 0 ) ) );
	while ( !q.empty() ){
		w = q.top().first;
		u = q.top().second.first;
		used = q.top().second.second;
		q.pop();
		if ( d[used][u] < w ) continue;
		if ( u == t ) return w;
		for ( int i=0; i < (int)G1[u].size(); ++i ){
			v = G1[u][i]; we = W1[u][i];
			if ( w + we < d[used][v] ){
				d[used][v] = w + we;
				q.push( piii( we + w, pii( v, used ) ) );
			}
		}
		if ( !used ){
			for ( int i=0; i < (int)G2[u].size(); ++i ){
				v = G2[u][i]; we = 0;
				if ( w + we < d[1][v] ){
					d[1][v] = w + we;
					q.push( piii( w + we, pii( v, 1 ) ) );
				}
			}
		}
	}
	return INT_MAX;
}

int main(){
	int M, F, S, T;
	int u, v, w;
	scanf("%d %d %d %d %d", &N, &M, &F, &S, &T);
	
	while ( M-- ){
		scanf("%d %d %d", &u, &v, &w);
		G1[u].push_back(v); W1[u].push_back(w);
		G1[v].push_back(u); W1[v].push_back(w);
	}
	
	while ( F-- ){
		scanf("%d %d", &u, &v);
		G2[u].push_back(v);
	}
	printf("%lld\n", dijkstra(S,T));
	return 0;
}

