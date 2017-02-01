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

double calc( int N ){

	double res = 1.0;

	for ( int i = 2; i <= N-2; i+=2 ) res *= i;
	for ( int i = 3; i <= N-1; i+=2 ) res /= i;

	return res;

}

int main(){

	int N;

	while ( scanf("%d",&N) != EOF ){
		printf("%.5lf\n",calc(N));
	}

	return 0;
}

