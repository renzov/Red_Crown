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
int A[MAXN];
int M[MAXN];
int pref[MAXN];

int main(){
	freopen ("homework.out","w",stdout);
	freopen("homework.in","r",stdin);	
	int N;
	int sum = 0;
	scanf("%d", &N);
	for ( int i=0; i < N; ++i ){
		scanf("%d", A + i);
		sum += A[i];
	}

	M[N-1] = A[N-1];
	for ( int i=N-2; i >= 0; i-- ) M[i] = min( A[i], M[i+1] );
	pref[0] = A[0];
	for ( int i=1; i < N; ++i ) pref[i] = pref[i-1] + A[i];

	int best = -1;
	int cnt = 1;
	int val;
	long long right, left;

	for ( int i=0; i < N-2; ++i ){
		val = sum - pref[i] - M[i+1];
		left = 1LL * cnt * val;
		right = 1LL * best * ( N - i  - 2 );
		if ( left > right ){
			best = val, cnt = N - i  - 2;
		}
	}

	for ( int i=0; i < N - 2; ++i ){
		val = sum - pref[i] - M[i+1];
		left = 1LL * cnt * val;
		right = 1LL * best * ( N - i  - 2 );
		if ( left == right ) printf("%d\n", i + 1);
	}

	return 0;
}

