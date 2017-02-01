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
#include <cassert>

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

const int MAXN = 15;
const int MAXF = 5100;
int N;
long long L;
long long d[MAXN][MAXN];
int subsets[MAXN][1<<13];
int size[MAXN];

int p[MAXN + 5];
long long A[MAXF];
long long B[MAXF];
int sa, sb;

void gen_perm( long long *V, int &sz, const int &s, const int &S, const int &t ){
	int m = 0;
	p[m++] = s;
	for ( int i=0; (1<<i) <= S; ++i ) 
		if ( (S>>i) & 1 ) p[m++] = i;
	p[m++] = t;
	sz = 0;
	long long l;
	int prev, act;
	do {
		l = 0;
		prev = s;
		for ( int i=0; i < m; ++i ){
			act = p[i];
			l += d[prev][act];
			prev = act;
			if ( l > L ) break;
		}
		if ( l <= L ) V[sz++] = l;
	}
	while ( next_permutation( p+1, p+(m-1) ) );
	sort( V, V + sz );
}

bool possible(){
	int all_bits = (1 << (N-1)) - 1;
	int S;
	for ( int k=0; k < size[N]; ++k ){
		S = subsets[N][k];
		for ( int mid=0; mid < (N-1); ++mid ){
			if ( (S >> mid)&1 ){
				gen_perm( A, sa, N-1, S^(1<<mid), mid );
				gen_perm( B, sb, mid, S^all_bits, N-1 );
				int i = 0, j = sb - 1;
				while ( i < sa && j >= 0 ){
					if (A[i]+B[j] == L) return true;
					if (A[i]+B[j] < L) ++i;
					else if (A[i]+B[j] > L) --j;
				}
			}
		}
	}
	return false;
}

void gen_subsets(){
	int all_bits;
	for ( int n=2; n < MAXN; ++n ){
		all_bits = ( 1 << (n-1) ) - 1;
		int &sz = size[n];
		sz = 0;
		for ( int S=1; S <= all_bits; ++S ){
			if ( __builtin_popcount(S) == (n>>1) ){
				subsets[n][sz++] = S;
			}
		}
	}
}

int main(){
	gen_subsets();
	while ( scanf("%d %lld", &N, &L) != EOF ){
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				scanf("%lld", d[i] + j);
		if ( possible() ) puts("possible");
		else puts("impossible");
	}
	return 0;
}

