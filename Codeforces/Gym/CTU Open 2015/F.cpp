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

const int MAXN = 5005; 

int s[MAXN];
int m[MAXN];
int d[MAXN];
int b[MAXN];

int a[MAXN*MAXN];

int main(){
	int L, S, M, D, B;

	while ( scanf("%d %d %d %d %d", &L, &S, &M, &D, &B) && L > 0 ){
		for ( int i=0; i<S; ++i ) scanf("%d", s+i);
		for ( int i=0; i<M; ++i) scanf("%d", m+i);
		for ( int i=0; i<D; ++i ) scanf("%d", d+i);
		for ( int i=0; i<B; ++i) scanf("%d", b+i);	

		int size = 0;
		for ( int i=0; i < S; ++i )
			for ( int j=0; j < M; ++j )
				a[size++] = s[i] + m[j];

		sort( a , a + size );
		long long res = 0;
		int val, idx;
		for ( int i=0; i < D; ++i )
			for ( int j=0; j < B; ++j ){
				val = L - d[i] - b[j];
				if ( val > 0 ){
					idx = lower_bound( a, a+size, val + 1 ) - a;
					idx--;
					res += (idx + 1);
				}
			}
		printf("%I64d\n", res);
	}
	return 0;
}

