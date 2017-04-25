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

char a[1005];
char b[1005];

bool compare( char *a, char *b, const int &bit ){
	for ( int i=0; a[i]; ++i )
		if ( abs(a[i] - b[i]) != bit ) return false;
	return true;
}

int main(){
	int N;

	scanf("%d", &N);
	scanf("%s %s", a, b);
	if ( compare(a,b, N&1) ) puts("Deletion succeeded");
	else puts("Deletion failed");
	return 0;
}

