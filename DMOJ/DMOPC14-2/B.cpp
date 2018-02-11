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

const int MAXL = 1024;
char S[MAXL];
int size[MAXL];

int main(){
	int L;
	int N = 0;
	scanf("%d %s", &L, S);
	int i = 0;
	while ( i < L && S[i] == 'X' ) i++;
	while ( i < L ){
		size[N] = 0;
		while ( i < L && S[i] == 'O' ) size[N]++, i++;
		while ( i < L && S[i] == 'X' ) i++;
		N++;
	}
	
	printf("%d\n", N);
	for ( int i=0; i < N; ++i ){
		for ( int j=0; j < size[i]; ++j ) putchar('O');
		puts("");
	}
	return 0;
}

