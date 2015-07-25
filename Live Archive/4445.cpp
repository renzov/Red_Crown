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

int N;
int X[10];
int Y[10];
double best;
bool used[10];
int idx[10];

bool check(int id){
	for ( int i=0; i < N; ++i )
		if ( i != id && !used[i] && Y[i] < X[id] )
			return false;
	return true;
}

bool test( double gap ){
	double last = (double) X[ idx[0] ];
	for ( int i=1; i<N; ++i ){
		if ( (last + gap) > Y[ idx[i] ] && fabs( Y[ idx[i] ] - last - gap ) > 0.00001 )
			return false;
		last = max( last + gap , (double)X[ idx[i] ] );
	}
	return true;
}

void backtrack( int pos ){
	if ( pos == N ){
		double l = 0;
		double r = 1441.0 * 60;
		double m;
		while ( (r - l) > 0.00001 ){
			m = ( l + r ) / 2.0;
			if ( test(m) ) 
				l = m;
			else 
				r = m;
		}
		best = max( best , l );
		return;
	}
	for ( int i=0; i < N; ++i ){
		if ( !used[i] && check(i) ){
			used[i] = true;
			idx[pos] = i;
			backtrack( pos + 1 );
			used[i] = false;
		}
	}
}

int main(){
	for ( int cases=1; scanf("%d",&N) && N ; ++cases ){
		for ( int i=0; i < N; ++i ){
			scanf("%d %d",X+i,Y+i);
			X[i] *= 60;
			Y[i] *= 60;
			used[i] = false;
		}
		best = 0.0;
		backtrack( 0 );
		best += 0.5;
		int M = ((int) best) / 60;
		int S = (int) (best - M*60);
		printf("Case %d: %d:%02d\n", cases, M , S);
	}
	return 0;
}

