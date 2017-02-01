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

const int MAXL = 16;
const int MAXN = 11;
const int BLACK = 0;
const int WHITE = 1;
const int MAXV = 1520;
const int MAXC = 21;
const int MAXM = 32770;
int L,C,N,M,V;

char guess[MAXN][MAXL];
int resp[MAXN][2];
int valid[ MAXV ];
char s[MAXM][MAXL];
char tmp[MAXL];

pii cmp( char *X , char *Y ){
	int w = 0, b = 0;
	int fx[MAXC] = {0};
	int fy[MAXC] = {0};

	for ( int i=0; i < L; ++i)
		if ( X[i] == Y[i] ) b++;
		else {
			fx[ X[i] - 'A' ]++;
			fy[ Y[i] - 'A' ]++;
		}

	for ( int i=0; i < C; ++i )
		w += min( fx[i] , fy[i] );

	return make_pair( b , w );
}

void gen_all_poss( int i ){
	if ( i == L ){
		tmp[i] = '\0';
		pii res;
		bool ok = true;
		for ( int j=0; j < N && ok; ++j ){
			res = cmp( guess[j] , tmp );
			if ( res.first != resp[j][BLACK] || 
				 res.second != resp[j][WHITE] ) 
				ok = false;  
		}

		if ( ok ) valid[ V++ ] = M;
		strcpy( s[M] , tmp );
		M++;
		
		return;
	}
	char c;
	for ( int j=0; j < C; ++j ){
		tmp[i] = (char)('A' + j);
		gen_all_poss( i + 1 );
	}
}

int uncertainty( int p ){

	int H[MAXL][MAXL] = {0};	
	int maxi = 0;
	pii res;
	int t;

	for ( int i=0; i < V; ++i ){
		if ( valid[i] != p ){
			res = cmp( s[p] , s[ valid[i] ] );
			t = ++H[ res.first ][ res.second ];
			if ( t > maxi ) maxi = t;
		}
	}
	return maxi;
}

int main(){
	int runs;

	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d %d %d",&L,&C,&N);
		for ( int i=0; i < N; ++i ){
			scanf("%s %d %d",guess[i],&resp[i][BLACK],&resp[i][WHITE]);
		}
		M = 0;
		V = 0;
		gen_all_poss(0);

		//printf("Valid %d\n",V);

		int mini = INT_MAX;
		int u;
		int idx;
		for ( int i=0; i < M; ++i ){
			u = uncertainty( i );
			if ( u < mini ){
				mini = u;
				idx = i;
			}
		}
		printf("%s %d\n",s[idx],mini);
	}
	return 0;
}

