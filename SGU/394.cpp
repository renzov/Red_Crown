#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<long long, pii> event;
const int MAXN = 100005;

long long X[MAXN];
long long Y[MAXN];
long long Y1[MAXN];
long long Y2[MAXN];
long long W[MAXN];
long long P[3*MAXN];
event E[3*MAXN];
int seg[4*3*MAXN];

inline int left( const int &x ){ return x << 1; }
inline int right( const int &x ){ return (x << 1) | 1; }

void build( const int &node, const int &L, const int &R ){
	seg[node] = 0;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	build( left(node), L, M );
	build( right(node), M + 1, R );
}

void update( const int &node, const int &L, const int &R, const int &p, const int &v ){
	if ( L == R ){
		seg[node] += v;
		return;
	}
	int M = ( L + R ) >> 1;
	if ( p <= M ) update( left(node), L, M, p, v );
	else update( right(node), M + 1, R, p, v );
	seg[node] = seg[ left(node) ] + seg[right(node)];
}

int query( const int &node, const int &L, const int &R, const int &l, const int &r ){
	if ( L == l && r == R ) return seg[node];
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query( left(node), L, M, l, r );
	if ( l > M ) return query( right(node), M + 1, R, l, r );
	return query( left(node), L, M, l, M ) + query( right(node), M + 1, R, M + 1, r );
}

int main(){
	
	int N, K;
	int M = 0;
	int Q = 0;
	long long x, y, w;

	scanf("%d %d", &N, &K);
	K++;
	for ( int i=0; i < N; ++i ){
		scanf("%lld %lld %lld", &x, &y, &w );
		X[i] = x + y, Y[i] = x - y, W[i] = w;
		P[M++] = x - y - w;
		P[M++] = x - y + w;
		P[M++] = x - y;
	}
	sort( P , P + M );
	M = unique( P, P + M ) - P;

	for ( int i=0; i < N; ++i ){
		x = X[i], y = Y[i], w = W[i];
		Y[i] = lower_bound( P, P + M, y ) - P;
		Y1[i] = lower_bound( P, P + M, y - w ) - P;
		Y2[i] = lower_bound( P, P + M, y + w ) - P;
		E[Q++] = event( x - w, pii( -1, i ) );
		E[Q++] = event( x, pii( 0, i ) );
		E[Q++] = event( x + w, pii( 1, i ) );
	}	
	sort( E, E + Q );
	build( 1, 0, M - 1 );
	int idx;
	vector<int> res;
	for ( int i=0; i < Q; ){
		x = E[i].first;
		for ( ; i < Q && E[i].first == x; ++i ){
			idx = E[i].second.second;
			switch( E[i].second.first ){
				case 1:	// Delete
						update( 1, 0, M - 1, max(0, (int)Y1[idx] - 1), -1 );
						update( 1, 0, M - 1, (int)Y2[idx], 1 );						
						break;
				case 0:	// Query
						if ( Y[idx] > 0 && query( 1, 0, M - 1, 0, (int)Y[idx] - 1 ) >= K )
							res.push_back( idx + 1 );	
						
						break;
				case -1: // Insert
						update( 1, 0, M - 1, max(0, (int)Y1[idx] - 1), 1 );
						update( 1, 0, M - 1, (int)Y2[idx], -1 );
						break;
			}
		}
	}
	sort( res.begin(), res.end() );
	printf("%d\n", (int)res.size());
	if ( (int)res.size() > 0 ){
		for ( int i=0; i < (int) res.size(); ++i ){
			if (i) putchar(' ');
			printf("%d", res[i]);
		}
		puts("");
	}
	return 0;
}
