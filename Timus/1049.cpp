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

int d[10005] = {0};
map<int,int> coef;

void sieve(){
	d[1] = 1;
	d[2] = 2;
	for ( int i=4; i <= 10000; i+=2 ) d[i] = 2;

	for ( int i=3; i < 100; i += 2 ){
		if ( d[i] == 0 ){
			d[i] = i;
			for ( int j=i*i; j < 10000 ; j += (i<<1) )
				if ( d[j] == 0 ) d[j] = i;
		}
	}
}

void factor(int n){
	int f;
	int cnt;

	while ( n != 1 ){
		cnt = 0;
		f = d[n];
		do {
			n /= f;
			cnt++;
		}
		while ( f == d[n] );
		coef[ f ] += cnt;
	}
}

int main(){
	int N,res;

	sieve();
	for ( int i=3; i <= 10000; i += 2 ) 
		if ( d[i] == 0 ) d[i] = i;

	res = 1;
	for ( int i=0; i < 10; ++i ){
		scanf("%d",&N);
		factor(N);
	}
	res = 1;
	for ( map<int,int>::iterator it = coef.begin(); it != coef.end() ; it++ ){
		res *= ( 1 + it->second );
		res %= 10;
	}
	printf("%d\n",res);
	return 0;
}

