/* INPUT SPEC. in Judge IS WRONG !!!!!!!!! SEE HOW TO PROCESS */
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
typedef pair< int , pair<int,int> > piii;

const int MAXN = 50500;

int N;
piii I[MAXN];
int sumUsed[MAXN];
int sumFree[MAXN];
bool Free[MAXN];
int L[MAXN];
int R[MAXN];
int size;

void init(){ /* Initialize data structures */
	sumUsed[0] = sumFree[0] = 0; L[0] = R[0] = -1;
	sumFree[1] = 1; sumUsed[1] = 0;
	Free[1] = true; 
	L[1] = R[1] = 0;
	size = 1;
}

void merge(){ /* merges two last blocks if they are of the same type */
	if ( size > 1 && Free[size] == Free[size-1] ){
		size--;
		sumFree[size] = sumFree[size+1];
		sumUsed[size] = sumUsed[size+1];
		R[size] = R[size+1];
	}
}

void update( int x ){
	if ( x > R[size] ){
		/* Add a new free block */
		size++;
		L[size] = R[size-1] + 1;
		R[size] = x;
		Free[size] = true;
		sumUsed[size] = sumUsed[size-1]; /* free block */
		sumFree[size] = sumFree[size-1] + (R[size] - L[size] + 1);
		merge();
	}
}

int find_used( int a ){ /* find used number from a to R[size] */
	int idx = lower_bound( L + 1, L + size + 1, a ) - L;
	if ( idx > size || L[idx] > a ) idx--;
	if ( Free[idx] ) return sumUsed[size] - sumUsed[idx];
	return sumUsed[size] - sumUsed[idx] + ( R[idx] - a + 1 );
}

void find_and_update( int a, int c ){
	int l = 0;
	int r = size;
	int m;
	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if ( (sumFree[size] - sumFree[m]) >= c )
			l = m;
		else 
			r = m;
	}
	/* 0 <= l < size , since c > 0 */ 
	/* blocks m+1 ... size have the desired ints */
	if ( (sumFree[size] - sumFree[l]) == c ){ /* collapse all blocks */
		R[l + 1] = R[size];
		Free[l + 1] = false;
		sumFree[l + 1] = sumFree[l];
		sumUsed[l + 1] = sumUsed[l] + (R[l + 1] - L[l + 1] + 1);
		size = l + 1;
		merge();
	}
	else {
		c -= (sumFree[size] - sumFree[l+1]); /* by invariant, sumF[size] - sumF[l+1] < c */
		R[l + 2] = R[ size ];		
		R[l + 1] -= c; /* R[l+1] - L[l+1] + 1 > c  */
		sumFree[l + 1] -= c;
		/* colapse blocks l+2 ... size, if l+2 > size create new block */
		L[l + 2] = R[ l + 1 ] + 1;
		Free[ l + 2 ] = false;
		sumFree[l + 2] = sumFree[ l + 1 ];
		sumUsed[l + 2] = sumUsed[ l + 1 ] + ( R[ l + 2 ] - L[ l + 2 ] + 1 );
		size = l + 2;
	}
}


void process( int a, int b, int c ){
	int covered = find_used(a);
	if ( covered < c ){
		c -= covered;
		find_and_update( a , c );
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		init();
		for  ( int i=0; i < N; ++i ){
			scanf("%d %d %d", &I[i].second.first, &I[i].first, &I[i].second.second);
		}
		sort( I , I + N );
		for ( int i=0; i < N; ++i ){
			update( I[i].first );
			process( I[i].second.first , I[i].first, I[i].second.second );
		}
		printf("%d\n", sumUsed[size]);
		if (runs) puts("");
	}
	return 0;
}
