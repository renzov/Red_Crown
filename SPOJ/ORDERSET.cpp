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

const int MAXN = 200005;

int a[MAXN + 5];
char op[MAXN + 5];
int val[MAXN + 5];

int cnt[4*MAXN + 16] = {0};
bool act[MAXN + 5] = {0};

void update( int node, int L, int R, int p, int v ){
	if (L==R){
		cnt[node] += v;
		return;
	}
	
	int M = (L+R) >> 1;
	int left = node << 1;
	int right = left + 1;

	if ( p <= M ) update( left, L , M , p , v );
	else update( right , M+1 , R , p , v );

	cnt[node] = cnt[left] + cnt[right];
}

int query_k( int node , int L , int R, int k ){
	if ( L == R ){
		return a[L];
	}

	int left = node << 1;
	int right = left + 1;
	int M = (L+R) >> 1;

	if ( cnt[left] >= k ) return query_k(left, L , M, k);
	else return query_k(right, M+1, R, k - cnt[left]);
}

int query( int node, int L , int R, int l ,int r ){
	if ( r < L || R < l ) return 0;
	if ( l <= L && R <= r ) return cnt[node];

	int left = node << 1;
	int right = left + 1;
	int M = (L+R) >> 1;

	return query( left , L , M ,  l , r ) + query( right, M+1, R , l , r );
}

int main(){

	int Q;
	int N = 0;

	scanf("%d",&Q);

	for ( int i=0; i<Q; ++i ){
		scanf(" %c %d",op + i,val + i);
		if (op[i] == 'I'){
			a[N++] = val[i];
		}
	}
	
	sort(a , a + N);
	N = unique( a , a + N ) - a;
	int pos;
	int total = 0;

	for ( int i=0; i < Q; ++i ){
		if (op[i] == 'I'){
			pos = lower_bound( a , a + N , val[i] ) - a;
			if ( !act[pos] ){ 
				update( 1 , 0 , N-1, pos, 1 );
				act[pos] = true;
				total++; 
			}
		}
		else if (op[i] == 'D'){
			pos = lower_bound( a , a + N , val[i] ) - a;
			if (a[pos] == val[i] && act[pos]){
				update( 1, 0, N-1, pos, -1 );
				act[pos] = false;
				total--;
			}
		}
		else if (op[i] == 'K'){
			if ( total < val[i] ) puts("invalid");
			else {
				printf("%d\n",query_k( 1 , 0 , N-1, val[i] ));
			}
		}
		else {
			pos = lower_bound( a , a + N , val[i]) - a;
			pos--;
			if ( pos < 0 ) puts("0");
			else printf("%d\n",query( 1 , 0 , N-1, 0 , pos ));
		}
	}
	return 0;
}

