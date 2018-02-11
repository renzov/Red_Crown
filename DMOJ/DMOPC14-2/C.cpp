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

const int MAXN = 55000;
int A[MAXN];
int B[MAXN];

int main(){
	
	int N;

	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", A+i);
	for ( int i=0; i < N; ++i ) scanf("%d", B+i);
	sort( A , A + N );
	sort( B, B + N );
	reverse( B, B + N );
	long long res = 0;
	for ( int i=0; i < N; ++i )
		res += A[i]*B[i];
	printf("%lld\n", res);
	return 0;
}

