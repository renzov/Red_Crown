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
#include <climits>

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

const int MAXN = 100006;
char w[MAXN];
int f[30];
int M;

int main(){
	int K;
	int runs;
	int cnt;
	int res, temp;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%s %d", w, &K);
		memset( f,  0, sizeof(f) );
		for ( int i=0; w[i]; ++i ){
			f[ w[i]-'a' ]++;
		}
		
		sort( f , f + 27);
		M = 0;
		while ( f[M] == 0 ) M++;
		res = INT_MAX;
		int last = -1;
		if ( M == 26 ){ 
			puts("0");
			continue;
		}
		for ( int i=M; i < 27; ++i ){
			if ( f[i] != last ){
				temp = 0;
				for ( int j=M; j < i; ++j )
					if ( f[j] < f[i] ) temp += f[j];
				for ( int j=i+1; j < 27; ++j ){
					if ( (f[j] - f[i]) > K ){
						temp += (f[j] - f[i] - K);
					}
				}
				if ( temp < res ) res = temp;
				last = f[i];
			}
		}
		printf("%d\n", res);
	}
	return 0;
}

