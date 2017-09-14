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

const int MAXN = 24;

int B, T;
int V[MAXN];
vector<int> S[128];

int val( const int &mask ){
	bool ok;
	for ( int i=0; i < T; ++i ){
		ok = false;
		for ( int j=0; j < (int) S[i].size() && !ok; ++j ){
			if ( ( mask >> S[i][j] ) & 1 ) ok = true;
		}
		if ( !ok ) return -1;
	}
	int res = 0;
	for ( int i=0; i < B; ++i ){
		if ( !((mask >> i) & 1) ) res += V[i];
	}
	return res;
}

int main(){
	int M;

	scanf("%d", &B);
	for ( int i=0; i < B; ++i )
		scanf("%d", V + i);

	scanf("%d", &T);
	int mask = 0;
	for ( int i=0; i < T; ++i ){
		scanf("%d", &M);
		S[i].resize(M);
		for ( int j=0; j < M; ++j ){
			scanf("%d", &S[i][j]);
			S[i][j]--;
		}
	}

	int res = 0; 
	for ( int mask=1; mask < (1<<B); ++mask ){
		res = max( res , val(mask) );
	}
	printf("%d\n", res);
	return 0;
}
