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

const int MAXN = 105;

char s[MAXN][15];
long long A[MAXN][26];
long long B[MAXN][MAXN]; 

long long Abs( long long x ){ return x<0? -x:x; }

long long gcd( long long x , long long y ){
	return (!y)? x : gcd( y , x % y );
}

void init( int N ){
	for ( int i = 0;  i < N; ++i )
		for ( int j=0; j < 26; ++j )
			A[i][j] = 0;
	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			B[i][j] = ( i == j )? 1:0;
}

void swap_rows( int R , int C, int x , int y ){
	long long tmp;
	for ( int i=0; i < C; ++i ){
		tmp = A[x][i];
		A[x][i] = A[y][i];
		A[y][i] = tmp;
	}
	for ( int i=0; i < R; ++i ){
		tmp = B[x][i];
		B[x][i] = B[y][i];
		B[y][i] = tmp;
	}
}

int solve( int R , int C ){
	int rank = 0;
	int r = 0;
	long long d = 1;
	int piv;
	//Gaussian Elimination , Fraction-free
	for ( int c = 0; c < C ; c++ ){
		//Search for pivot;
		for ( piv = r; piv < R && A[piv][c] == 0 ; piv++ );
		
		if ( piv < R ){
			rank++;

			if ( piv != r ) swap_rows( R , C , r , piv );
			
			for ( int i=r+1; i < R; ++i ){
				for ( int j=c+1; j < C; ++j ){
					A[i][j] = (A[i][j]*A[r][c] - A[r][j]*A[i][c]) / d;
				}
				for ( int j=0; j < R; ++j ){
					B[i][j] = (B[i][j]*A[r][c] - B[r][j]*A[i][c]) / d;
				}
				A[i][c] = 0;
			}
			
			if (d){
				d = A[r][c];
			}
			r++;
		}
	}

	if ( rank < R ){
		long long g = Abs(B[rank][0]);
		for ( int i=1; i < R && g > 1 ; ++i ){
			g = gcd( Abs(B[rank][i]) , g );
		}
		if ( g > 1 ){
			for ( int i=0; i < R; ++i ) B[rank][i] /= g;
		}
	}
	return rank;
}

int main(){
	int n;

	while ( scanf("%d",&n) && n ){
		init(n);
		for ( int i=0; i < n; ++i ){
			scanf("%s",s[i]);
			for ( int j=0; s[i][j] ; ++j ){
				A[ i ][ s[i][j] - 'a' ]++;
			}
		}
		int rank = solve( n , 26 );
		if ( rank == n ) puts("no");
		else {
			puts("yes");
			for ( int i=0; i < n; ++i ){
				printf("%s ",s[i]);
				if (B[rank][i] > 0){
					putchar('L');
				}
				else if (B[rank][i] < 0){
					putchar('R');
				}
				else {
					putchar('N');
				}
				printf(" %lld\n",Abs(B[rank][i]));
			}
		}
	}
	return 0;
}

