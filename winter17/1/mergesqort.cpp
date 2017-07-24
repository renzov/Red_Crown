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

map<int, long long > memo;

long long solve( int n ){
	if ( n <= 1 ) return 0;
	if ( memo.find(n) != memo.end() ) return memo[n];
	int left = (int) sqrt(n);
	return memo[n] = (long long)n + solve(left) + solve(n-left);
}

int main(){	
	int n;
	scanf("%d", &n);
	printf("%lld\n", solve(n));
	return 0;
}

