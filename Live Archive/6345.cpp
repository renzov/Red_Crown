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

const int MAXN = 55;

int main(){
	char s[MAXN];
	int f[MAXN];
	int runs;
	int res;
	int N, M, K;

	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d %d", &N, &M, &K);
		priority_queue< pii > q;
		res = 0;
		for ( int i=0; i < N; ++i ){
			scanf("%s", s);
			f[i] = 0;
			for ( int j=0; j < M; ++j )
				if ( s[j] == '*' ) f[i]++;
			q.push( pii( M - 2*f[i], i ) );
			res += f[i];
		}
		pii temp;
		for ( int i=0; i < K; ++i ){
			temp = q.top();
			q.pop();
			res += temp.first;
			f[ temp.second ] += temp.first;
			q.push( pii( M - 2*f[ temp.second ] , temp.second ) );
		}
		printf("%d\n", res);
	}
	return 0;
}
