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

const int MAXH = 100000;

int deg[MAXH];
int out[MAXH];
int U[MAXH + 5];
int V[MAXH + 5];
int pos[MAXH];
int ord[MAXH];

bool cmp( const int &a, const int &b ){
	return deg[a] < deg[b];
}

int main(){
	int u,v;
	int H,R;
	int M;
	while ( scanf("%d %d",&H,&R) && H && R ){

		for ( int i=0; i < H; ++i ){
			out[i] = deg[i] = 0;
			ord[i] = i;
		}
		for ( int i=0; i<R; ++i ){
			scanf("%d %d",&u,&v);
			u--,v--;
			U[i] = u, V[i] = v;
			deg[u]++,deg[v]++;
		}
		sort( ord , ord + H , cmp );

		for ( int i=0; i < H; ++i ) pos[ ord[i] ] = i;

		for ( int i=0; i < R; ++i ){
			if 	( pos[ U[i] ] < pos[ V[i] ] )
				out[ U[i] ]++;
			else 
				out[ V[i] ]++;
		}
		
		M = 0;
		
		for ( int i = H - 1; i >= 0 && out[ ord[i] ] == (H - i - 1); --i )
			M++;

		// The last M vertices are the members of the clique
		// Now check if its valid
		bool valid = true;
		int left = H - M;
		for ( int i=0; i < R && valid; ++i ){
			if ( pos[ U[i] ] < left && pos[ V[i] ] < left )
				valid = false;
		}
		if (valid) puts("Y");
		else puts("N");
	}
	return 0;
}

