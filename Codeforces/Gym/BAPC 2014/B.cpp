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
const int MAXN = 16;

int n, t;
int b[MAXN];
int d[3605];
int q[3605];
int qt, qf;
int main(){
	int runs, u, v;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &n, &t);
		for ( int i=0; i < n; ++i ) scanf("%d", b+i);
		fill( d , d + 3601, -1 );
		d[ 0 ] = 0;
		qf = qt = 0;
		q[qt++] = 0;
		while ( qf < qt && d[t] == -1 ){
			u = q[qf++];
			for ( int i=0; i < n; ++i ){
				v = min( max( 0 ,  u + b[i] ) , 3600 );
				if ( d[v] == -1 ){
					d[v] = d[u] + 1;
					q[qt++] = v;
				}
			}
		}
		for ( int i=t; i <= 3600; ++i ){
			if ( d[i] != -1 ){
				printf("%d %d\n", d[i], i - t );
				break;
			}
		}
	}
	return 0;
}

