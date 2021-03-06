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
#include <cassert>

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

const int MAXN = 100;
int M;
long long MOD;
int N;
int P[MAXN];
vector<int> res;

void preprocess(){
	M = 0;
	bool ok;
	for ( int i=2; i <= 70; ++i ){
		ok = true;
		for ( int j=0; j < M && ok; ++j ){
			if ( i % P[j] == 0 ) ok = false;
		}
		if ( ok ) P[M++] = i;
	}
}

void backtrack( const int &n, const int &idx, const long long &prod ){
	res.push_back( prod );
	for ( int i=idx; i < M && P[i] <= n; ++i )
		backtrack( n - P[i], i, (prod * P[i]) % MOD );
}

int main(){
	int runs;
	preprocess();
	
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %lld", &N, &MOD);
		backtrack( N, 0, 1LL );
		sort( res.begin(), res.end() );
		printf("%d\n", unique( res.begin(), res.end() ) - res.begin() );
		if ( runs ) res.clear();
	}
	return 0;
}

