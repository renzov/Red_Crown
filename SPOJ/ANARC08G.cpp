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

const int MAXN = 1024;

int D[MAXN];
int R[MAXN];

int main(){
	int N;
	int x;
	int sum;
	int cases = 0;

	while (scanf("%d", &N) && N){
		sum = 0; 
		cases++;
		fill( D , D + N, 0 );
		fill( R , R + N, 0 );

		for ( int i=0; i < N; ++i ){
			for ( int j=0; j < N; ++j ){
				scanf("%d",&x);
				D[i] += x;
				R[j] += x;
				sum += x;
			}
		}
		
		int res = 0;

		for ( int i=0; i < N; ++i ){
			if (D[i] > R[i]) res += (D[i] - R[i]);
		}
		
		printf("%d. %d %d\n", cases, sum, res);
	}
	return 0;
}

