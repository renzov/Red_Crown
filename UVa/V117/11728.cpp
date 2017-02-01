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
const int MAXS = 1002;

int res[ MAXS ];

void preprocess(){
	int num;
	fill( res , res + 1001 , -1 );

	res[1] = 1;

	for ( int i=2; i < 1000 ; ++i ){
		num = 1 + i;
		for ( int j=2; j < i; ++j ){
			if ( !(i % j) ){
			
				num += j;

				//if (j*j != i) 
				//	num += (i/j);
			}
		}
		if ( num <= 1000 ) res[ num ] = i;
	}

}

int main(){

	preprocess();
	int n;
	int runs = 0;
	while ( scanf("%d",&n) && n ){
		runs++;
		printf("Case %d: %d\n",runs,res[n]);
	}
	return 0;
}

