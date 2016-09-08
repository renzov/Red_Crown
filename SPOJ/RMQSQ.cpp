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
#include <climits>

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
const int LOG = 18;

int ST[LOG][MAXN];	//SPARSE TABLE for RMQ

int main(){
	int len;
	int N,Q;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ) scanf("%d", &ST[0][i]);
	len = 1;
	for ( int i=1; i < 18; ++i ){
		for ( int j=0; j < N; ++j ){
			ST[i][j] = ( ((1<<i) + j) <= N )? min(ST[i-1][j], ST[i-1][j+len]):INT_MAX;
		}
		len <<= 1;
	}
	int x,y,z;
	int size;
	scanf("%d", &Q);
	while ( Q-- ){
		scanf("%d %d", &x, &y);
		if ( x > y ) swap(x,y);
		size = y - x + 1;
		if ( size == 1 ) printf("%d\n", ST[0][x]);
		else {
			len = 0;
			while ( (1 << len) <= size ) len++;
			len--;
			z = y - (1 << len) + 1;
			printf("%d\n", min( ST[len][x], ST[len][z] ));
		}
	}
	return 0;
}
