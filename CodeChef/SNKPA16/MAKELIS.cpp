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

int main(){
	int runs, K, last, temp;
	int beg, ext, p;
	int res[200];
	int sur[200];

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &K);
		if ( K == 1 ){
			puts("1");
			puts("1");
			continue;
		}
		temp = K;
		for ( int i=0; temp > 0; ++i ){
			if ( temp & 1 ){
				last = i;
			}
			temp >>= 1;
		}
		int sum = 0;
		for ( int i=last-1, k = 1; i >= 0; --i, ++k ){
			if ( (K >> i) & 1 ){
				sur[i] = k - sum;
				sum += sur[i];
			}
			else {
				sur[i] = 0;
			}
		}
		beg = sum + 1;
		ext = 1;
		p = 0;
		for ( int i=last-1; i >= 0; i-- ){
			res[p++] = beg + 1;
			res[p++] = beg;
			beg +=2;
			for ( int j=0; j < sur[i]; ++j ) res[p++] = ext++;
		}
		printf("%d\n", beg - 1);
		printf("%d", res[0]);
		for (int i=1; i < p; ++i) printf(" %d", res[i]);
		puts("");
	}
	return 0;
}

