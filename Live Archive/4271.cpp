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

int N, M;
int e;

const int MAXN = 10005;
const int MAXE = 300005;

int from[MAXE];
int to[MAXE];
int cap[MAXE];
int flow[MAXE];
int nxt[MAXE];
int head[MAXN];

int q[MAXN];
int qf, qt;
int pre[MAXN];

void add_edge( const int &u, const int &v ){
	from[e] = u, to[e] = v, cap[e] = 1, flow[e] = 0, nxt[e] = head[u], head[u] = e, e++;
	from[e] = v, to[e] = u, cap[e] = 1, flow[e] = 0, nxt[e] = head[v], head[v] = e, e++;
}

bool augment_path( const int &s, const int &t ){
	qf = qt = 0;	
	q[ qt++ ] = s;

	int u, v, f;
	fill( pre, pre + N, -1 );

	while ( qf < qt && pre[t] < 0 ){
		u = q[qf++];
		for ( f=head[u]; f >= 0; f=nxt[f] ){
			v = to[f];
			if ( pre[v] == -1 && ( flow[f^1] || !flow[f] ) ){
				pre[v] = f;
				q[qt++] = v;
			}
		}
	}
	if ( pre[t] == -1 ) return false;
	v = t;
	while ( v != s ){
		f = pre[v];
		u = from[ f ];
		if ( flow[f^1] ){
			flow[f^1]--;
		}
		else {
			flow[f]++;
		}
		v = u;
	}
	return true;
}

int main(){
	int u, v;
	int cases = 0;
	int S, T;

	while ( scanf("%d %d", &N, &M) && N ){
		// Init
		e = 0;
		fill( head, head + N, -1 );
		// Read the graph
		for ( int i=0; i < M; ++i ){
			scanf("%d %d", &u, &v);
			u--, v--;
			add_edge(u, v);
		}
		scanf("%d %d", &S, &T);
		S--, T--;
		printf("Case %d: ", ++cases);
		if ( augment_path( S, T ) && augment_path(S,T) )
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

