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

const int MAXN = 200005;

int X1[MAXN];
int X2[MAXN];
long long SL[MAXN];
long long S[MAXN] = {0};
int H;

int find_index( int left, int r ){
	int m;
	int l = left;
	while ( r - l > 1 ){
		m = ( l + r ) >> 1;
		if (S[m] - S[left] <= H) l = m;
		else r = m;
	}
	return l;
}

int main(){
	int N;
	int gap;
	scanf("%d %d", &N, &H);
	for ( int i=0; i < N; ++i ){
		scanf("%d %d", X1+i, X2+i);
		if ( i ) SL[i] = SL[i-1] + (X2[i] - X1[i]);
		else SL[i] = X2[i] - X1[i];
		if ( i > 0 ){
			gap = X1[i] - X2[i - 1];
			S[i] = S[i - 1] + gap;
		}
	}
	S[N] = S[N-1] + H + 2000;
	long long best = 0;
	for ( int i=0; i < N; ++i ){
		int idx = find_index( i, N ); // index of element does not surpass H
		long long res;
		if ( i ) res = SL[idx] - SL[i-1] + H;
		else res = SL[idx] + H;
		best = max( res, best );
	}
	printf("%I64d\n", best);
	return 0;
}

