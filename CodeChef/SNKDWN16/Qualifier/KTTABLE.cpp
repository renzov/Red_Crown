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

const int MAXN = 10005;

int A[MAXN];
int B[MAXN];

int main(){
	int N;
	int runs;
	int res;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d", &N);
		A[0] = 0;
		for ( int i=1; i <= N; ++i ) scanf("%d", A + i);
		for ( int i=1; i <= N; ++i ) scanf("%d", B + i);
		res = 0;
		for ( int i=1; i <= N; ++i )
			if ( (A[i-1] +  B[i]) <= A[i] ) res++;
		printf("%d\n", res);
	}
	return 0;
}
