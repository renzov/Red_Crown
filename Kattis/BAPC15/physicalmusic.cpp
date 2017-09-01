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

const int MAXN = 100005;

int P[MAXN];
int L[MAXN];

int main(){
	int N;
	int runs;
	scanf("%d", &runs);
	
	while ( runs-- ){
		scanf("%d", &N);
		set<int> pos;
		
		for ( int i=1; i <= N; ++i ){ 
			scanf("%d", P + i);
		}
		// Process the music in the order in the download list
		int res = 0;
		for ( int i=N; i >= 1; --i ){
			// See if there is an element in i + 1 ... N 
			// That has a better position in download list
			pos.insert( P[i] );
			if ( pos.lower_bound( P[i] ) != pos.begin() ){
				L[res++] = P[i];
			}
		}
		if ( res ) sort( L, L + res );
		printf("%d\n", res);
		for ( int i=0; i < res; ++i  ) printf("%d\n", L[i]);
	}
	return 0;
}

