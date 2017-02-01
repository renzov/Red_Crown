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

int X1[MAXN];
int X2[MAXN];
int Y1[MAXN];
int Y2[MAXN];

bool inter( int a, int b ){
	int xmin = min( X2[a], X2[b] );
	int xmax = max( X1[a], X1[b] );
	int ymin = min( Y2[a], Y2[b] );
	int ymax = max( Y1[a], Y1[b] );

	if ( xmin <= xmax  || ymin <= ymax )
		return false;
	return true;
}


int main(){
	int L,W;
	int N;
	int runs;
	long long sum;
	bool outside;
	bool overlap;

	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d %d",&W,&L);
		scanf("%d",&N);
		sum = 0;
		overlap = outside = false;
		for ( int i=0; i < N; ++i ){
			scanf("%d %d %d %d",X1 + i, Y1 + i, X2 + i, Y2 + i );
			sum += (X2[i] - X1[i]) * (Y2[i] - Y1[i]);
			outside |= (X2[i] > W || X1[i] < 0 || Y1[i] < 0 || Y2[i] > L);
		}
		for ( int i=0; i < N && !overlap; ++i ){
			for ( int j=i+1; j < N && !overlap; ++j ){
				if (inter(i,j))
					overlap = true;
			}
		}
		if ( overlap ) puts("NONDISJOINT");
		else if ( outside ) puts("NONCONTAINED");
		else if ( sum != 1LL*W*L ) puts("NONCOVERING");
		else puts("OK");
	}
	return 0;
}

