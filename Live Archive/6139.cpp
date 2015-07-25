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

const int MAXN = 100002;

int prod[5 * MAXN];
int a[MAXN + 5];

int sign(int x){ 
	if (x==0) return 0;
	return (x>0)? 1:-1;
}

void update( int node , int L , int R , int p , int val ){
	if (L==R){
		a[p] = prod[node] = val;
		return;
	}
	int M = (L + R) >> 1;
	int left = node << 1;
	int right = left + 1;

	if (p <= M) update(left, L, M, p , val);
	else update(right, M+1, R, p, val);

	prod[node] = prod[left] * prod[right];
}

int query( int node, int L, int R, int l, int r ){
	if (r < L || R < l) return 1;
	if ( l <= L && R <= r ) return prod[node];

	int M = (L + R) >> 1;
	int left = node << 1;
	int right = left + 1;

	return query(left, L, M, l , r) * query( right, M+1, R, l, r );
}

void build(int node, int L, int R){	
	if (L==R){
		prod[node] = a[L];
		return;
	}
	int left = node << 1;
	int right = left + 1;
	int M = (L+R) >> 1;
	
	build(left, L, M);
	build(right, M+1, R);

	prod[node] = prod[left] * prod[right];
}

int main(){
	int x;
	char op;
	int res;
	int V,I,J;
	int N,K;

	while (scanf("%d %d",&N,&K) != EOF){
		for ( int i=1; i <= N; ++i ){
			scanf("%d",&x);
			a[i] = sign(x);
		}
		build( 1 , 1 , N );
		while (K--){
			scanf(" %c", &op);
			if (op == 'C'){
				scanf("%d %d",&I,&V);
				if ( sign(V) == a[I] ) continue;
				update( 1 , 1 , N , I , sign(V) );
			}
			else {
				scanf("%d %d",&I,&J);
				res = query( 1 , 1 , N , I , J );
				if (res > 0) putchar('+');
				else if (res < 0) putchar('-');
				else putchar('0');
			}
		}
		puts("");
	}
	return 0;
}

