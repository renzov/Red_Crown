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

const int MAXN = 100005;

int a[MAXN];
int fl[MAXN];
int fr[MAXN];
int maxL[MAXN];
int maxR[MAXN];

bool pos[MAXN];

int main(){
	int S,N;
	int runs;
	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d",&S,&N);
		for ( int i=1; i <= N; ++i ){
			scanf("%d",a+i);
		}
		for ( int i=1; i <= S; ++i ) fl[i] = fr[i] = 0;
		// Calculete maxL and maxR
		maxL[0] = maxR[N+1] = 0;
		int cnt = 0;
		for ( int i=1,j=N; i <= min(S,N); ++i,--j ){
			fl[ a[i] ]++;
			fr[ a[j] ]++;
			maxL[ i ] = max( maxL[i-1] , fl[ a[i] ] );
			maxR[ j ] = max( maxR[j+1] , fr[ a[j] ] );
			
			if ( fl[ a[i] ] == 1 ) cnt++;
			else if ( fl[ a[i] ] == 2 ) cnt--;
		}
		for ( int i=1,j=S+1; i <= (N-S); ++i, ++j ){
			pos[i] = cnt == S;
			// Remove a[i]
			fl[ a[i] ]--;
			if ( fl[ a[i] ] == 0 ) cnt--;
			else if ( fl[ a[i] ] == 1 ) cnt++;
			// Put a[j]
			fl[ a[j] ]++;
			if ( fl[ a[j] ] == 1 ) cnt++;
			else if ( fl[ a[j] ] == 2 ) cnt--;
		}
		if (N >= S) pos[ N-S+1 ] = cnt == S;

		int res = 0;
		bool ok;
		int t;
		for ( int i=1; i <= S; ++i ){
			if ( i <= N ){
				if ( maxL[i-1] <= 1 ){
					t = i;
					ok = true;
					while ( ok && (t + S - 1) <= N ){
						ok &= pos[t];
						t += S;
					}
					ok &= (maxR[t] <= 1);
					if (ok) res++;
				}
			}
			else {
				if ( maxL[N] <= 1 ) res++;
			}
		}
		//printf("%d\n",res);
		cout << res << endl;
	}
	return 0;
}
