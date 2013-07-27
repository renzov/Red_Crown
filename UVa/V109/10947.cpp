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
const double EPS = 1e-6;
bool G[200][200];
int X[200],Y[200];
int R[200];
double D;

bool comp( double a, double b ){
	if ( fabs( a - b ) < EPS ) return true;
	return a <= D;
}

double d( int i, int j ){
	return hypot( abs(X[i] - X[j])*1.0 , abs(Y[i] - Y[j])*1.0 );
}

int main(){
	int K,M;
	int N;
	while ( scanf("%d %d",&K,&M) != EOF ){
		scanf("%d %d %d",&X[0],&Y[0],&R[0]);
		scanf("%d %d %d",&X[1],&Y[1],&R[1]);
		scanf("%d",&N);
		D = M * K;
		for ( int i=2; i < (N + 2) ; ++i ){
			scanf("%d %d %d",&X[i],&Y[i],&R[i]);
		}
		N += 2;
		for ( int i=0; i < N; ++i ){
			G[i][i] = true;
			for ( int j=i+1; j < N; ++j )
				G[i][j] = G[j][i] = comp( d(i,j) - (R[i] + R[j]) , D );
			}
		for ( int k=0; k < N; ++k )
			for (int i=0; i < N; ++i)
				for ( int j=0; j < N; ++j )
					G[i][j] |= ( G[i][k] & G[k][j] );
		if ( G[0][1] )
			puts("Larry and Ryan will escape!");
		else 
			puts("Larry and Ryan will be eaten to death.");
	}
	return 0;
}

