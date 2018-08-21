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

int N;
int V[MAXN];
int inv[MAXN];
int p[MAXN];

inline int find_set(const int &x){
	return p[x] == x? x:( p[x] = find_set(p[x]) );
}

int main(){
	int u, v;
	int M;

	scanf("%d %d", &N, &M);
	for ( int i=0; i < N; ++i ){ 
		scanf("%d", V + i);
		V[i]--;
		inv[ V[i] ] = i;
		p[i] = i;
	}
	while ( M-- ){
		scanf("%d %d", &u, &v);
		u--, v--;
		u = find_set(u), v = find_set(v);
		if ( u != v ){
			p[v] = u;
		}
	}
	
	int res = 0;
	for ( int i=0; i < N; ++i )
		if ( find_set( i ) == find_set( inv[i] ) ) res++;

	printf("%d\n", res);

	return 0;
}

