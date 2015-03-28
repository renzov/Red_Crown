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
const int MOD = 1000000;

vector< vector<int> > dp;
int N,M;
int p,q,k;

inline int get( int x , int i ){
	return (x >> i)&1;
}

void search( int i ){
	if ( i >= N ){
		dp[k+1][q] += dp[k][p];
		dp[k+1][q] %= MOD;
	}

	if ( get(p,i) ){
		search(i+1);
		return;
	}

	if ( i > 0 && !get(q,i-1) && !get(q,i) ){
		q ^= ( 1 << i ); q ^= ( 1 << (i-1) );
		search( i + 1 );
		q ^= ( 1 << i ); q ^= ( 1 << (i-1) );
	}

	if ( (i + 2) <= N ){
	
		if ( !get(q,i) && !get(q,i+1) ){
			q ^= ( 1 << i ); q ^= ( 1 << (i+1) );
			search(i+1);
			q ^= ( 1 << i ); q ^= ( 1 << (i+1) );
		}

		if ( !get(p,i+1) ){
		
			if ( !get(q,i) && !get(q,i+1) ){
				q ^= ( 1 << i ); q ^= ( 1 << (i+1) );
				search(i + 2);
				q ^= ( 1 << i ); q ^= ( 1 << (i+1) );
			}

			if ( !get(q,i) ){
				q ^= ( 1 << i );
				search( i + 2 );
				q ^= ( 1 << i );
			}

			if ( !get(q,i+1) ){
				q ^= ( 1 << (i+1) );
				search(i+2);
				q ^= ( 1 << (i+1) );
			}

		}
	}
}

int main(){

	while ( scanf("%d %d",&N,&M) && N ){
		
		dp = vector< vector<int> > ( M + 1 , vector<int> ( 1 << N , 0 )  );
		dp[0][0] = 1;

		for ( k=0; k < M; ++k ){
			for ( p = 0; p < (1<<N) ; ++p ){
				if ( dp[k][p] ){
					q = 0;
					search(0);
				}
			}
		}
		printf("%d\n",dp[M][0]);
	}
	return 0;
}

