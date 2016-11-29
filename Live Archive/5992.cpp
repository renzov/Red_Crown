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
#include <climits>
#include <list>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 505;

int R, C;
char G[MAXN][MAXN];
int D[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};


int main(){
	int runs;
	int nx, ny;	
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &R, &C);
		for ( int i=0; i < R; ++i )
			scanf("%s", G[i]);

		list< pii > Q[2];
		list< char > L[2];
		// init
		for ( int i=0; i < R; ++i )
			for ( int j=0; j < C; ++j ){
				visited[i][j] = false;
				if ( G[i][j] == '.' ) D[i][j] = INT_MAX;
				else if ( G[i][j] == '#' ) D[i][j] = -1;
				else D[i][j] = 0, Q[0].push_back( pii(i,j) ), L[0].push_back( G[i][j] );
			}
		int cur = 0;
		pii pos;
		char c;
		do {	
			while ( !Q[cur].empty() ){
				pos = Q[cur].front();
				c = L[cur].front();
				Q[cur].pop_front();
				L[cur].pop_front();
				if ( !visited[pos.X][pos.Y] && isalpha( G[ pos.X ][ pos.Y ] ) ){
					visited[ pos.X ][ pos.Y ] = true;
					for ( int k=0; k < 4; ++k ){
						nx = pos.X + dx[k];
						ny = pos.Y + dy[k];
						if ( nx < 0 || nx >= R || ny < 0 || ny >= C ) continue;
						if ( G[nx][ny] != '#' && G[nx][ny] != '*' && (D[nx][ny] >= (D[pos.X][pos.Y] + 1)) ){
							D[nx][ny] = D[pos.X][pos.Y] + 1;
							Q[1-cur].push_back( pii(nx, ny) );
							L[1-cur].push_back( c );
						}
					}	
				}
			}
			cur = 1 - cur;
			list<pii>::iterator it = Q[cur].begin();
			list<char>::iterator it2 = L[cur].begin();
			for ( ; it != Q[cur].end(); it++, it2++ ){
				if ( isalpha( G[it->X][it->Y] ) && G[it->X][it->Y] != *it2 ){
					G[it->X][it->Y] = '*';
				}
				else if ( G[it->X][it->Y] == '.' ){
					G[it->X][it->Y] = *it2;	
				}
			}
		}
		while ( !Q[cur].empty() );

		for ( int i=0; i < R; ++i ){
			for ( int j=0; j < C; ++j )
				putchar(G[i][j]);
			putchar('\n');
		}
		puts("");
	}
	return 0;
}

