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
int A[MAXN];
int N, K;

int main(){

	while ( scanf("%d %d", &N, &K) != EOF ){
		bool ok = true;
		int idx = 0;

		for ( int i=0; i < K; ++i ){ 
			scanf("%d", A+i);
		}
		
		// looking for increasing substring
		while ( idx + 1 < K && A[idx] < A[idx+1] && ok ){
			if ( (A[idx + 1] <= 2) || (A[idx+1] - A[idx] > 2) ) ok = false;
			idx++;
		}
		// Special case
		if ( A[idx] <= 2 && K > 1 ) ok = false;
		// Checking the deacreasing substring
		for ( int i=idx; i < K - 1 && ok; ++i ){
			if ( A[i] <= A[i+1] ) ok = false;
			else if ( A[i] <= 2 || (A[i] - A[i+1] > 2) ) ok = false;
		}
		// Final check
		if ( idx == 0 || idx == (K-1) ){
			ok &= ( N >= A[idx] ); //Useless check
		}
		else {
			ok &= ( A[idx - 1] != A[idx + 1] );
		}

		if ( ok ) puts("S");
		else puts("N");
	}

	return 0;
}

