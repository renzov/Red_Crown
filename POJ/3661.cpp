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

const int MAXN = 10005;

int D[MAXN];
int dp[MAXN];
int N, M;

int main(){	
	int sum;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ) scanf("%d", D + i);

	dp[N] = 0;
	for ( int i=N-1; i >= 0; --i ){
		// descansamos
		dp[i] = dp[i+1];
		sum = 0;
		for ( int j=0; j < M && (i + 2*(j+1)) <= N; ++j ){
			sum += D[i + j];
			dp[ i ] = max( dp[i] , dp[ i + 2*(j + 1) ] + sum );
		}
	}
	printf("%d\n", dp[0]);
	return 0;
}

