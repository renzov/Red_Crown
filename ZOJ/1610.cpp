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

const int MAXN = 8001;
const int NOCOLOR = -2;
const int MULT = -1;

int color[5 * MAXN + 15];
int lazy[5 * MAXN + 15];
int cnt[MAXN + 10];

int last_int;
int last_color;

void build( int node , int L, int R ){
	
	color[node] = NOCOLOR;
	lazy[node] = -1;

	if ( L==R ){
		return;
	}
	
	int left = (node << 1);
	int right = (node << 1) + 1;
	int M = ( L + R ) >> 1;

	build( left , L , M );
	build( right , M + 1 , R );
}

void push( int node , int c , int L , int R ){
	color[node] = c;
	if ( L != R ) lazy[node] = c;
}

void update( int node, int l, int r, int L, int R, int c ){
	
	if ( l > R || r < L ) return;
	
	if ( l <= L && r >= R ){
		color[node] = c;
		if (L != R) lazy[node] = c;
		return;
	}
	
	int left = node << 1;
	int right = left + 1;
	int M = (L+R) >> 1;

	if ( lazy[node] > -1 ){
		push(left,lazy[node], L , M );
		push(right,lazy[node], M + 1 , R );
		lazy[node] = -1;
	}

	update( left , l , r , L , M , c );
	update( right , l , r , M + 1 , R , c );

	if ( color[left] == MULT || color[right] == MULT || 
		 color[left] != color[right] ){
		color[node] = MULT;
	}
	else {
		color[node] = color[left];
	}
}

void query( int node, int L , int R ){
	
	if ( color[node] == NOCOLOR ) return;
	
	if ( color[node] != MULT ){
		//printf("[%d %d] -> %d\n",L,R,color[node]);
		if ( last_color == color[node] ){
			//puts("Entramos igual color");
			//printf("last_int = %d\n",last_int);
			if ( (L - last_int) != 1 ) cnt[last_color]++;
			last_int = R;
		}
		else {
			cnt[ color[node] ]++;
			last_int = R;
			last_color = color[node];
		}
		return;
	}
	int left = node << 1;
	int right = left + 1;
	int M = (L+R) >> 1;
	if ( lazy[node] > -1 ){
		push(left, lazy[node], L , M );
		push(right, lazy[node], M + 1 , R );
		lazy[node] = -1;
	}
	query( left , L , M );
	query( right , M + 1 , R );
}

int main(){	
	int n,l,r,c;
	while (scanf("%d",&n) != EOF){
		build( 1 , 0 , 7999 );

		for (int i=0; i < n; ++i){
			scanf("%d %d %d",&l,&r,&c);
			update( 1 , l , r - 1 , 0 , 7999 , c );
		}
		
		fill( cnt , cnt + 8001 , 0 );

		last_int = -2;
		last_color = -2;

		query( 1 , 0 , 7999 );
		
		for (int i=0; i <= 8000; ++i){
			if (cnt[i]) printf("%d %d\n",i,cnt[i]);
		}
		puts("");
	}
	return 0;
}

