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

const int MAXN = 1024;

int N, X, Y;
int T = 0;
int tm[MAXN][MAXN] = {0};
double dp[MAXN][MAXN];

inline double binom( int x ){ return (double)x*(x-1)/2; }

double solve( int w, int l ){
	// w number of people I defeat
	// l number of people beat me
	if ( w < 0 || l < 0 ) return 0.0;
	if ( w == 0 && l == 0 ){
		return (Y == 1)? 1.0:0.0;
	}
	if ( (w + l + 1) < Y ) return 0.0;
	double allpairs = binom( w + l + 1 );
	if ( (w + l + 1) == Y ){
		return l / allpairs; 
	}
	if ( tm[w][l] < T ){
		tm[w][l] = T;
		dp[w][l] = 0.0;
		dp[w][l] += binom(w) * solve(w-1, l) / allpairs;
		dp[w][l] += binom(l) * solve(w, l-1) / allpairs;
		dp[w][l] += l * w * solve(w-1,l) / allpairs;
		dp[w][l] += w * solve(w-1, l) / allpairs;
	}
	return dp[w][l];
}

int main(){
	int W, L;
	while ( scanf("%d %d %d", &N, &X, &Y) != EOF ){
		T++;
		L = X - 1;
		W = N - X;
		printf("%.4f\n", solve(W, L));
	}
	return 0;
}

