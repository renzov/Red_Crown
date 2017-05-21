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
typedef pair< long long , long long > pii;

const int MAXK = 200002;
pii P[MAXK];
long long V[2*MAXK];
long long dp[2*MAXK] = {0};

int main(){
	long long x, y;
	int K;
	long long N;

	scanf("%I64d %d", &N, &K);
	for ( int i=0; i < K; ++i ){
		scanf("%I64d %I64d", &x, &y);
		V[2*i] = x, V[2*i + 1] = y;
		P[i].first = y, P[i].second = x;
	}
	sort( P, P + K ); 	// process intervals increasing by ending 
	sort( V, V + 2*K );
	int M = unique( V, V + 2*K ) - V; // 0 ... M - 1 diff. values
	
	for ( int i=0; i < K; ++i ){
		P[i].first = lower_bound( V , V + M, P[i].first ) - V;
		P[i].second = lower_bound( V, V + M, P[i].second ) - V;
		P[i].first++, P[i].second++;	// index from 1 ... M
	}
	
	int j = 0;
	long long best;
	for ( int i=1; i <= M; ++i ){
		best = 0LL;
		while ( j < K && P[j].first == i ){
			x = P[j].first, y = P[j].second;
			best = max( best, (V[x-1] - V[y-1] + 1) + dp[y - 1]);
			j++;
		}
		dp[i] = max( dp[i-1], best );
	}
	printf("%I64d\n", N - dp[M]);
	return 0;
}

