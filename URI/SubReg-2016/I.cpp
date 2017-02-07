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

const int MAXN = 50005;
int H[MAXN];
int L[MAXN];
int R[MAXN];
int N;

int main(){
	scanf("%d", &N);		
	for ( int i=0; i < N; ++i ) scanf("%d", H+i);
	L[0] = 1;
	for ( int i=1; i<N; ++i ) L[i] = min( H[i], L[i-1] + 1 );
	R[N-1] = 1;
	for ( int i=N-2; i >= 0; --i ) R[i] = min( H[i], R[i+1] + 1 );
	int res = 0;
	for ( int i=0; i < N; ++i ) res = max( res , min(L[i], R[i]) );
	printf("%d\n", res);
	return 0;
}
