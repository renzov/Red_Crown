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
typedef pair< long long , int > pii;

const int MAXR = 256;

int N, R, K;
long long P[MAXR];
long long acc[MAXR][MAXR];
long long reach[MAXR];
bool vis[MAXR];

void gcdext(long long A, long long  B, long long &D, long long &x, long long &y) {
  if (B == 0) { x = 1; y = 0; D = A; return; }
  gcdext(B, A % B, D, x, y);
  long long x1 = y;
  long long y1 = x - y * (A / B);
  x = x1;
  y = y1;
}

int pos( int u, long long t ){
	long long q = t / K;
	int r = t % K;
	long long res = q * acc[u][K-1] + P[u];
	if ( r > 0 ) res += acc[u][r-1];
	return res % N;
}

long long get_time( int u, int v, const long long &start ){
	int beg = start % K;
	long long nxt;

	if ( acc[u][K-1] < acc[v][K-1] ) swap( u , v );
	
	// Solve A x = B ( mod N )
	long long A = acc[u][K-1] - acc[v][K-1];
	long long B, D, x, y;
	long long res = LLONG_MAX;

	if ( A == 0 ){
		for ( int k=0; k < K; ++k ){
     		nxt = start + (k - beg + K) % K;  
			B = pos( v , nxt ) - pos( u , nxt ); 
			if ( B == 0 ){
				res = nxt;
				res = min( nxt, res );
			}
		}
	} 
	else {
		gcdext( A, N, D, x, y );
		for ( int k=0; k < K; ++k ){
     		nxt = start + (k - beg + K) % K;  		
			B = (pos( v , nxt ) - pos( u , nxt ) + N) % N;
			if ( B % D == 0 ){
				long long n = -x*B / N;
				long long m = x * (B/D) + n * (N/D);
        		if (m < 0) m += N/D;
				res = min(res, nxt + m * K);	
			}
		}
	}
	return res;
}

int main(){
	long long sum;
	long long t;
	long long val;
	int u;

	while ( scanf("%d %d %d", &N, &R, &K) != EOF ){
		for ( int i=0; i < R; ++i ){
			scanf("%lld", P + i ); 
			P[i]--;
		}
		// Calculate the accumulated sums of jumps
		for ( int i=0; i < R; ++i ){
			sum = 0;
			for ( int j=0; j < K; ++j ){
				scanf("%lld", &val);
				sum += val;
				acc[i][j] = sum;
			}
		}
		// Find the times 
		fill( reach, reach + R, LLONG_MAX );
		fill( vis, vis + R, false );
		reach[0] = 0;
		priority_queue< pii, vector<pii>, greater<pii> > q;
		q.push( pii( 0 , 0 ) );
		while ( !q.empty() ){
			u = q.top().second;
			q.pop();
			if ( vis[u] ) continue;
			vis[u] = true;
			for ( int v=0; v < R; ++v ){
				if ( !vis[v] ){
					t = get_time( u , v, reach[u] );
					if ( t < reach[v] ) {
						reach[v] = t;
						q.push( pii( reach[v], v ) );
					}
				}
			}
		}
		int cnt = 0;
		long long res = 0;
		for ( int i=0; i < R; ++i ) 
			if ( vis[i] ){  
				cnt++;
				res = max( res, reach[i] );	
			}
		printf("%d %lld\n", cnt, res);
	}
	return 0;
}

