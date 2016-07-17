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

int main(){
	int runs;
	int N;
	long long A, size[ 100 ];
	size[0] = 1;
	size[1] = 1;
	size[2] = 2;
	size[3] = 2;
	int n = 4;
	long long last = 2;
	for ( int i=0; i < 16; ++i ){
		last *= 3;
		size[n++] = last;
		last *= 2;
		size[n++] = last;
		last *= 2;
		size[n++] = last;
		size[n++] = last;
	}

	scanf("%d", &runs);
	int idx, grundy;
	long long sum;
	while ( runs-- ){
		scanf("%d", &N);
		grundy = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%lld", &A);
			sum = 0LL;
			idx = 0;
			while ( sum <= A ){
				sum += size[idx];
				idx++;
			}
			idx--;
			idx %= 4;
			grundy ^= idx;
		}
		if ( grundy ){
			puts("Henry");
		}
		else {
			puts("Derek");
		}
	}	
	return 0;
}

