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
char A[MAXN];
char B[MAXN];
int f[30] = {0}; // For counting frequecies

int main(){

	int runs;
	int N, D;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &D);
		scanf("%s %s", A, B);
		bool ok = true;

		if ( D >= N ){
			if ( strcmp(A,B) == 0 ) printf("Yes\n");
			else printf("No\n");
			continue;
		}
		
		for ( int i=0; i < 26; ++i ) f[i] = 0;

		for ( int i=0; i < D  && ok; ++i ){

			for ( int j=i; j < N; j += D ){
				f[ A[j] - 'a' ]++; 
				f[ B[j] - 'a' ]--;
			}
			

			for ( int j=0; j < 26 && ok; ++j ){
				if ( f[j] != 0 ) ok = false;
			}
		}

		if ( ok ) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

