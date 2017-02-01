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
const int MOD = 20437;

int n;
char M[30][30];

int d[20][20];
int c[20][20];

int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};
int m;

struct triple {
	int first;
	int second;
	char L;
	triple(){}
	triple( char l ,int x , int y ){
		L = l;
		first = x;
		second = y;
	}
	bool operator<(const triple &that) const {
		return L < that.L;
	}
};

triple pos[30];

void bfs( int sx, int sy , char b , char e ){
	for ( int i=0; i < n; ++i )
		for ( int j=0; j < n; ++j ){
			d[i][j] = -1;
			c[i][j] = 0;
		}

	d[sx][sy] = 0;
	c[sx][sy] = 1;
	int x,y,nx,ny;
	int k=0;
	queue< pii > q[2];
	q[0].push( make_pair(sx,sy) );
	int t = 0;
	while ( !q[t].empty() ){
		k++;
		while ( !q[t].empty() ){
			x = q[t].front().first;
			y = q[t].front().second;
			q[t].pop();

			for ( int i=0; i < 4; ++i ){
				nx = x + dx[i];
				ny = y + dy[i];
				if ( nx < 0 || ny < 0 || nx >= n || ny >= n ) continue;
				if ( M[nx][ny] == '.' || M[nx][ny] == b || M[nx][ny] == e ){
					if ( d[nx][ny] == -1 ){
						d[nx][ny] = d[x][y] + 1;
						q[1-t].push( make_pair( nx , ny ) );
					}
					if ( (d[x][y] + 1) == d[nx][ny] ){
						c[nx][ny] += c[x][y];
						c[nx][ny] %= MOD;
					}
				}
			}
		}
		t = 1 - t;
	}
}

int main(){
	int runs=0;	
	while ( scanf("%d",&n) && n ){
		runs++;
		m = 0;
		for ( int i=0; i < n; ++i ){
			for ( int j=0; j < n; ++j ){
				scanf(" %c",&M[i][j]);
				if (  isalpha( M[i][j] ) ){
					pos[ m++ ] = triple(M[i][j],i,j);
				}
			}
		}

		if ( m==1 ){
			printf("Case %d: %d %d\n",runs,0,1);
			continue;
		}

		sort( pos , pos + m );
		int count = 1;
		int len = 0;
		for ( int i=0; i < (m-1); ++i ){
			bfs( pos[i].first , pos[i].second , pos[i].L , pos[i+1].L );	
			if ( d[ pos[i+1].first ][ pos[i+1].second ] == -1 ){
				len = -1; break; 
			}
			else {
				M[ pos[i].first ][ pos[i].second ] = '.'; 
				len +=  d[ pos[i+1].first ][ pos[i+1].second ];
				count *=  c[ pos[i+1].first ][ pos[i+1].second ];
				count %= MOD;
			}
		}
		if ( len < 0 ){
			printf("Case %d: Impossible\n",runs);
		}
		else {
			printf("Case %d: %d %d\n",runs,len,count);
		}
	}
	return 0;
}

