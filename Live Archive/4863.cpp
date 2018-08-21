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
int pA[MAXN];
int pB[MAXN];
int size[MAXN];
bool processed[MAXN];

pii E[MAXN]; 
int A, B;
int res;

void assign_place( const int &i ){
	int left;
	if ( pA[i] <= pB[i] ){ // Should go to A
		if ( size[i] <= A ){
			A -= size[i];
			res += pA[i]*size[i];
		}
		else {
			left = size[i] - A;
			res += pA[i] * A;
			A = 0;
			res += pB[i] * left;
			B -= left;
		}
	}
	else {
		if ( size[i] <= B ){
			B -= size[i];
			res += pB[i] * size[i];
		}
		else {
			left = size[i] - B;
			res += pB[i]*B;
			B = 0;
			res += pA[i]*left;
			A -= left;
		}
	}
}


int main(){
	int N;
	
	while ( scanf("%d %d %d", &N, &A, &B) && N ){
		res = 0;
		for ( int i=0; i < N; ++i ){
			processed[i] = false;
			scanf("%d %d %d", size + i, pA + i, pB + i);
			if ( pA[i] <= pB[i] ){
				E[i] = pii( pA[i] - pB[i], i );
			}
			else {
				E[i] = pii( pB[i] - pA[i], i );
			}
		}
		sort( E, E + N );
		int idx;
		for ( int i=0; i < N; ++i ){
			idx = E[i].second;
			assign_place( idx );
		}
		printf("%d\n", res);
	}

	return 0;
}

