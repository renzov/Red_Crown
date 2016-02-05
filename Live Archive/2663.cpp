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
typedef pair< int , pair<int,int> > piii;

const int MAXN = 50005;

piii I[MAXN];
int sum[MAXN];
int X[MAXN];
int Y[MAXN];
int size;

int search( int l , int r ){
	if ( Y[size] < l ) return size + 1;	
	if ( l <= X[1] ) return 0;
	if ( X[size] < l ) return size;

	int L = 1;
	int R = size;
	int m;
	while ( R - L > 1 ){
		m = (L + R) >> 1;
		if ( X[m] >= l ) 
			R = m;
		else
			L = m;
	}
	return L;
}

int overlap( int l , int r, int i ){
	if ( max( X[i] , l ) > min( Y[i] , r ) ) return 0;
	else return min( Y[i] , r ) - max( X[i], l )  + 1;
}

void update( int b , int c ){
	size++;
	X[size] = b - c + 1;
	Y[size] = b;
	sum[size] = c + sum[size-1];
}

int main(){

	int N;
	int a,b,c;
	int res;
	int idx, tmp;
	
	X[0] = Y[0] = -1;
	sum[0] = 0;

	while ( scanf("%d", &N) == 1 ){
		for ( int i=0; i<N; ++i ){
			scanf("%d %d %d", &a, &b, &c );
			I[ i ] = make_pair( b , make_pair( a , c ) );
		}
		sort( I , I + N );
		size = res = 0;
		for ( int i=0; i < N; ++i ){
			a = I[i].second.first;
			b = I[i].first;
			c = I[i].second.second;
			idx = search( a , b );
			if (idx > size){
				res += c;
				update( b , c );
			}
			else {
				tmp = overlap( a , b , idx ) + sum[size] - sum[idx];
				if ( tmp < c ){
					res += (c  - tmp);
					c -= tmp;
					update( b , c);
				}
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
