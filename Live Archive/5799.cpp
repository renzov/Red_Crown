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

int a[3];

bool has_next( const int &r, const int &e ){
	if ( e == 13 ) return false;
	if ( e + 1 != r ) return true;
	return e + 2 <= 13;
}

int main(){
	int rank, extra;

	while ( scanf("%d %d %d", a, a+1, a+2) && a[0] ){
		sort( a , a + 3 );
		if ( a[0] == a[2] ){ // A set
			if ( a[0] == 13 ) puts("*");
			else printf("%d %d %d\n", a[0] + 1, a[0] + 1, a[0] + 1);
			continue;
		}
		// Check if its a pair
		if ( a[0] == a[1] ){
			rank = a[0];
			extra = a[2];
		}
		else if ( a[1] == a[2] ){
			rank = a[1];
			extra = a[0];
		}
		else { // it has no pair
			printf("1 1 2\n");
			continue;
		}
		int sol[3];
		// We know its a pair
		if ( has_next( rank, extra ) ){
			if ( (extra + 1) == rank ) sol[0] = rank, sol[1] = rank, sol[2] = rank + 1;
			else sol[0] = rank, sol[1] = rank, sol[2] = extra + 1;
		}
		else {
			if ( rank == 13 ) sol[0] = 1, sol[1] = 1, sol[2] = 1;
			else sol[0] = rank + 1, sol[1] = rank + 1, sol[2] = 1;
		}
		sort( sol, sol + 3 );
		printf("%d %d %d\n", sol[0], sol[1], sol[2]);
	}
	return 0;
}

