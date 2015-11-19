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
int L[MAXN];
int R[MAXN];
int H[MAXN];
int S[MAXN];
long long sum[MAXN];

int main(){
	int N;
	int cases = -1;
	while ( scanf("%d",&N) != EOF ){
		cases++;
		if ( cases ) puts("");

		sum[0] = 0;
		for (int i=1; i <= N; ++i){ 
			scanf("%d",H+i);
			sum[i] = sum[i-1] + H[i];
		}
		H[0] = -1;
		H[N + 1] = -1;

		int sp = 0;
		int p;
		S[ sp++ ] = 1;
		p = 2;
		while ( sp > 0 ){
			while ( sp > 0 && H[ S[sp - 1] ] > H[p] ){
				R[ S[sp - 1] ] = p;
				sp--;
			}
			if ( p <= N ){
				S[ sp++ ] = p;
				p++;
			}
		}

		sp = 0;	
		S[ sp++ ] = N;
		p = N - 1;
		while ( sp > 0 ){
			while ( sp > 0 && H[ S[sp - 1] ] > H[p] ){
				L[ S[sp - 1] ] = p;
				sp--;
			}
			if ( p > 0 ){
				S[ sp++ ] = p;
				p--;
			}
		}

		long long best = (long long)H[1] * H[1];
		long long area;
		int l = 1,r = 1;
		for ( int i=1; i<=N; ++i ){
			area = (long long) H[i] * ( sum[ R[i] - 1 ] - sum[ L[i] ]  );
			if ( area > best || (area == best && r - l > R[i] - L[i] - 2) ){
				best = area;
				l = L[i] + 1;
				r = R[i] - 1;
			}
		}
		printf("%lld\n%d %d\n", best, l , r);
	}

	return 0;
}

