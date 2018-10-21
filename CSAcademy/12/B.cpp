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

const int MAXN = 100005;
int A[MAXN];

int main(){
	int N;	
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
	}
	A[N] = 0;
	int l = 0;
	long long m;
	long long res = 0;
	for ( int r=0; r <= N; ++r ){
		if ( A[r] == 0 ){
			m = r - l;
			res += ((m * ( m + 1 )) >> 1);
			l = r + 1;
		}
	}
	printf("%lld\n", res);
	return 0;
}

