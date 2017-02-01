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

const int MAX = 80005;
const int MAX_H = 1000000005;
int h[MAX];
int next[MAX];

int main(){

	int N;

	scanf("%d",&N);
	for ( int i=0; i < N ; ++i ){
		scanf("%d",h+i);
		next[i] = i + 1;
	}
	h[N] = MAX_H;
	long long res = 0;
	int c;
	for ( int i=N-1; i >= 0; --i ){
		c = 0;
		while ( next[i] < N && h[ next[i] ] < h[i] ){
			c += next[next[i]] - next[i]; 
			next[i] = next[ next[i] ];
		}
		res += c;
	}
	printf("%lld\n",res);
	return 0;
}

