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
const int MAXN = 1000005;

int n,d;

pii H[MAXN];
int Q[MAXN];
bool act[MAXN];

int reg( int p ){
	if (act[p-1] && act[p+1]) return 1;
	if (!act[p-1] && !act[p+1]) return -1;
	return 0;
}

int main(){

	int runs;

	scanf("%d",&runs);

	while (runs--){
	
		scanf("%d %d",&n,&d);
		for ( int i=1; i <= n ; ++i ){
			scanf("%d",&H[i].first);
			H[i].second = i;
			act[ i ] = true;
		}
		
		act[0] = act[n+1] = false;

		for ( int i=0; i < d ; ++i ){
			scanf("%d",Q + i);
		}

		sort( H + 1 , H + n + 1 );
		
		int p = 1;
		int cont = 1;

		for ( int i=0; i < d ; ++i ){
			while ( p <= n && H[p].first <= Q[i] ){
				cont += reg(H[p].second);
				act[ H[p].second ] = false;
				//printf("Eliminamos %d - cont %d\n",H[p].second,cont);
				p++;
			}
			if (i) putchar(' ');
			printf("%d", cont);
		}
		puts("");
	}
	return 0;
}
