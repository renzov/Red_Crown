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

const int MAXN = 200005;

char A[MAXN], B[MAXN];

int P[30][30];
int idx[30];

int main(){
	int N;
	scanf("%d", &N);
	scanf("%s %s", A, B);
	fill( idx, idx + 26, -1 );
	for ( int i=0; i < 26; ++i )
		for ( int j=0; j < 26; ++j )
			P[i][j] = -1;
	int res = 0;
	for ( int i=0; i < N; ++i ){
		if ( A[i] != B[i] ){ 
			res++;
			P[ A[i] - 'a' ][ B[i] - 'a' ] = i;
			idx[ A[i] - 'a' ] = i;
		}
	}
	if ( res == 0 ) printf("%d\n-1 -1\n", res);
	else {
		for ( int i=0; i < 26; ++i )
			for ( int j=i+1; j < 26; ++j ){
				if ( P[i][j] >= 0 && P[j][i] >= 0 ){
					printf("%d\n%d %d\n", res - 2, P[i][j] + 1, P[j][i] + 1);	
					return 0;
				}
			}
		
		for ( int i=0; i < N; ++i ){
			if ( A[i] != B[i] && idx[ B[i] - 'a' ] >= 0 ){ 
				printf("%d\n%d %d\n", res - 1, i + 1, idx[ B[i] - 'a'] + 1);
				return 0;
			}
		}
		printf("%d\n-1 -1\n", res);
	}
	return 0;
}
