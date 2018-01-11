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
const int MAXN = 60005;
char S[MAXN]; 
int idx[300];
long long cnt[4];
long long mul[4] = {1LL, 1000LL, 1000000LL, 1000000000LL};
map<long long,int> H;

long long get_idx(){
	return cnt[0]*mul[0] + cnt[1]*mul[1] + cnt[2]*mul[2] + cnt[3]*mul[3];
}

int main(){

	int runs;
	scanf("%d", &runs);
	int N, K;

	idx['A'] = 0, idx['C'] = 1, idx['G'] = 2, idx['T'] = 3;

	while ( runs-- ){
		scanf("%d", &K);
		fill( cnt, cnt + 4, 0 );
		scanf("%s", S);
		N = strlen(S);
		int res = 1; // Error: No Live Archive existem casos com K > N e a resposta eh 1.
		if ( K <= N ){
			for ( int i=0; i < K; ++i ){
				cnt[ idx[ S[i] ] ]++;
			}
			res = 1;
			H[ get_idx() ] = 1;
			for ( int i=K; i < N; ++i ){
				cnt[ idx[ S[i] ] ]++;
				cnt[ idx[ S[i-K] ] ]--;
				res = max( res , ++H[ get_idx() ] );
			}
		}
		printf("%d\n", res);
		if ( runs ){
			H.clear();
		}
	}
	return 0;
}

