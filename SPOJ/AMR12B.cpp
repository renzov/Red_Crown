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

const int MAXM = 300005;
const int MAXN = 1000005;
pii P[MAXM];
int out[MAXN];
int main(){
	int N,M;
	int runs, res;
	int k;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &N, &M);
		for ( int i=0; i < M; ++i ) scanf("%d %d", &P[i].first, &P[i].second);
		sort( P , P + M );
		if ( M == 0 ){
			printf("2 %d\n", N );
			continue;
		}
		fill( out + 1, out + N + 1, 0 );
		k = 0;
		bool loose = true;
		for ( int i=1; i <= N && loose; ++i ){
			while ( k < M && P[k].first < i ) k++;
			while ( k < M && P[k].first == i ){
				out[i]++;
				out[ P[k].second ]--;
				k++;
			}
			out[i] += ( i - 1 );
			if ( out[i] == (N-1) ){
				loose = false;
				res = i;
			}
		}
		if ( loose ) puts("1");
		else printf("2 %d\n", res);
	}
	return 0;
}

