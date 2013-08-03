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

const int MAXN = 100;

int X1[MAXN];
int X2[MAXN];
int Y1[MAXN];
int Y2[MAXN];
int N;
int G[MAXN][MAXN];
bool vis[MAXN];
int A[MAXN];

bool inside( int &x , int &y , int idx ){
	return  X1[idx] <= x && x <= X2[idx] &&
			Y1[idx] <= y && y <= Y2[idx];
}

bool alternating_path( int u ){
	if ( vis[u] ) return false;
	vis[u] = true;
	int v;	
	for ( int v = 0; v < N; ++v ){
		if ( G[u][v] == 1 ){
			if ( A[v] == -1 ){
				A[v] = u;
				return true;
			}
			else {
				if ( alternating_path( A[v] ) ){
					A[v] = u;
					return true;
				}
			}
		}
	}
	return false;
}

bool has_matching(){
	bool ok = true;
	fill( A , A + N , -1 );
	for ( int i=0; i < N && ok; ++i ){
		fill( vis , vis + N , false );
		ok = alternating_path( i );	
	}
	return ok;
}

int main(){
	int x,y;
	int runs = 0;

	while ( scanf("%d",&N) && N ){
		runs++;
		for ( int i=0; i < N; ++ i ){	
			scanf("%d %d %d %d",X1+i,X2+i,Y1+i,Y2+i);
			for ( int j=0; j < N; ++j ) G[i][j] = 0;
		}
	
		for ( int i=0; i < N; ++i ){
			scanf("%d %d",&x,&y);
			for ( int j=0; j < N; ++j )
				if ( inside( x , y , j ) ) 
					G[i][j] = 1;
		}
		
		printf("Heap %d\n",runs);

		if (!has_matching()) puts("none");
		else {
			int res[MAXN];
			int cnt = 0; 
			for ( int i=0; i<N; ++i ) res[i] = A[i];

			for ( int i=0; i < N; ++i ){
				G[ res[i] ][ i ] = 0;
				if (!has_matching()){
					if ( cnt ) putchar(' ');
					printf("(%c,%d)",(char)(i+'A'),res[i]+1);
					cnt++;
				}
				G[ res[i] ][ i ] = 1;
			}
			if ( !cnt ) puts("none");
			else puts("");
		}
		puts("");
	}

	return 0;
}

