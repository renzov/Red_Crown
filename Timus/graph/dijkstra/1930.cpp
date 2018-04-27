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
typedef pair< int, pii > piii;
int N;

const int MAXN = 10005;
vector<int> G[2][MAXN];
int d[2][MAXN];

int main(){
	int M;
	int u, v, w;
	int s, t;

	scanf("%d %d", &N, &M);
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		G[1][u].push_back(v);
		G[0][v].push_back(u);
	}
	scanf("%d %d", &s, &t);
	s--, t--;
	fill( d[0], d[0] + N, INT_MAX );
	fill( d[1], d[1] + N, INT_MAX );
	
	deque<pii> q;
	q.push_front( pii(s,0) );
	q.push_front( pii(s,1) );
	d[0][s] = d[1][s] = 0;
	
	int b;

	while ( !q.empty() ){
		u = q.front().first;
		b = q.front().second;
		q.pop_front();
		
		for ( int i=0; i < (int)G[b][u].size(); ++i ){
			v = G[b][u][i];
			if ( d[b][u] < d[b][v] ){
				d[b][v] = d[b][u];
				q.push_front( pii(v,b) );
			}
		}
		for ( int i=0; i < (int)G[1-b][u].size(); ++i ){
			v = G[1-b][u][i];
			if ( d[b][u] + 1 < d[1-b][v] ){
				d[1-b][v] = d[b][u] + 1;
				q.push_back( pii(v, 1-b) );
			}
		}
	}
	
	printf("%d\n", min( d[0][t], d[1][t] ));

	return 0;
}

