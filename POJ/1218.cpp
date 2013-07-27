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

int pot[ 15 ];

int main(){

	int runs;
	int n;
	int res;

	for ( int i=1; i <= 10 ; ++i )
		pot[i] = i*i;
	
	scanf("%d",&runs);

	while ( runs-- ){
		scanf("%d",&n);
		res = 1;
		while ( pot[res] < n ) res++;
		if ( pot[res] > n ) res--;
		printf("%d\n",res);
	}

	return 0;
}

