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
int N, M;
char L[MAXN][MAXN];
int H[MAXN];
int res[2*MAXN];

void solve(){
	stack< pii > S;
	int pos;
	int dy, dx;
	for ( int i=0; i < M; ++i ){
		pos = i;
		while ( !S.empty() && S.top().first >= H[i] ){
			pos = S.top().second;
			S.pop();
		}
		if ( H[i] == 0 ) continue;		
		if ( !S.empty() ){
			dy = H[i] - S.top().first;
			dx = pos - S.top().second;
		}	
		if ( !S.empty() && dx >= dy ){
			res[ S.top().first + i - S.top().second + 1 ]++;
		}
		else {
			S.push( pii( H[i] , pos ) );
			res[ i - pos + 1 + H[i] ]++;
		}
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		fill( H, H + M, 0 );
		fill( res, res + M + N + 1, 0 );
		for ( int i=0; i < N; ++i ){
			scanf("%s", L[i]);
		}

		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < M; ++j )
				if ( L[i][j] == '.' ) H[j]++;
				else H[j] = 0;
			solve();
		}
		for ( int i=1; i <= (N+M); ++i )
			if ( res[i] ) printf("%d x %d\n", res[i], 2*i);
	}
	return 0;
}

