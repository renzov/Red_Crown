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
bool isprime[1005] = {0};
int prime[1000];
bool dp[1005][3] = {0};

int P = 0;
void sieve(){
	prime[P++] = 2;
	for ( int i=3; i < 1000; i+= 2 ){
		if ( !isprime[i] ){
			prime[P++] = i;		
			for (int j=i*i; j <= 1000; j += (i<<1) )
				isprime[j] = true;
		}
	}
}

int main(){
	sieve();
	int runs;
	int N;

	scanf("%d", &runs);

	int res[1005][3];

	for ( int i=0; i < P; ++i ){
		dp[ prime[i] ][0] = true;
		res[ prime[i] ][0] = prime[i];
	}

	for ( int i=0; i < 2; ++i ){
		for ( int j=2; j < 1000; ++j ){
			if (dp[j][i]){
				for ( int k=0; k < P && ((j + prime[k]) <= 1000); ++k ){
					if (!dp[j+prime[k]][i+1]){
						dp[ j + prime[k] ][ i+1 ] = true;
						res[ j + prime[k] ][ i+1 ] = prime[k];
					}
				}
			}
		}
	}
	

	int R[3];
	while ( runs-- ){
		scanf("%d",&N);
		if ( !dp[N][2] ){
			puts("0");
			continue;
		}
		for (int i=2; i >= 0; --i){
			R[i] = res[N][i];
			N -= res[N][i];
		}
		sort(R, R+3);
		printf("%d %d %d\n", R[0], R[1], R[2]);
	}
	return 0;
}

