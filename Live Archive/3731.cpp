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
const int MAXN = 10;

int N,M;
int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};
bool done[180000];
int dp[180000];
int pot[12];

int game[MAXN][MAXN];
int pos[MAXN][MAXN];
int color[MAXN][MAXN];

int mx,my;

int dfs( int x , int y , int c ){
	int res = 1;
	int nx,ny;
	color[x][y] = c;
	for ( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || nx >= N || ny >= N || game[nx][ny] != c ) continue;
		if ( color[nx][ny] == -1 ) res += dfs( nx , ny , c );
	}
	return res;
}

int solve( int pl, int m , int state ){

	if (done[state]) return dp[state];
	
	done[state] = true;

	if ( m == M ){

		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				color[i][j] = -1;

		int area;
		int max0 = 0;
		int max1 = 0;

		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j )
				if ( color[i][j] == -1 ){
					area = dfs( i , j , game[i][j] );
					if ( game[i][j] == 0 )
						max0 = max( area , max0 );
					else 
						max1 = max( area , max1 );
				}
		dp[state] = max0 - max1;
		return dp[state];
	}

	int best = (pl == 0)? -INT_MAX:INT_MAX;
	int res;

	for ( int i=0; i < N; ++i )
		for ( int j=0; j < N; ++j )
			if ( game[i][j] == -1 ){
			
				game[i][j] = pl;
				res = solve( 1 - pl , m + 1 , pot[ pos[i][j] ]*( 1 + pl ) + state  );
				game[i][j] = -1;

				if ( pl && best > res ){
					if (!state){ mx = i; my = j; }
					best = res;
				}
				else if (!pl && best < res ){
					if (!state){ mx = i; my = j; }
					best = res;
				}
			}

	return dp[state] = best;
}

int main(){
	pot[0] = 1;
	for ( int i=1; i <= 11; ++i ) pot[i] = pot[i-1]*3;

	char s[11];
	int cnt;

	while ( scanf("%d",&N) && N ){
		
		cnt = M = 0;

		for ( int i=0; i < N; ++i ){
			scanf("%s",s);
			for ( int j=0; j < N; ++j ){
				switch ( s[j] ){
					case '0' : cnt++; game[i][j] = 0; pos[i][j] = -1; break;
					case '1' : cnt--; game[i][j] = 1; pos[i][j] = -1; break;
					case '.' : game[i][j] = -1; pos[i][j] = M++; break;
				}
			}
		}
	
		for ( int i=0; i < pot[M]; ++i ) done[i] = false;

		int res;

		if ( cnt > 0 ){ 
			res = solve( 1 , 0 , 0 );
			printf("(%d,%d) %d\n",mx,my,-res);
		}
		else {
			res = solve (0 , 0 , 0);
			printf("(%d,%d) %d\n",mx,my,res);
		}
	}
	return 0;
}

