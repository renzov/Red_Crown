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

const int MAXN = 202;
const int MAXC = 21000;
int N,M;
char G[MAXN][MAXN];
int C[MAXN][MAXN];
int deg[MAXN][MAXN];
int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};
vector<pii> ext;

bool bfs( int sx , int sy, int col ){
	int x,y;
	int nx,ny;
	bool res = true;
	queue< pii > q;
	q.push( make_pair(sx,sy) );

	while ( !q.empty() ){
		x = q.front().first;
		y = q.front().second;
		q.pop();

		C[x][y] = col; 

		for ( int i=0; i  < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			if ( nx < 0 || ny < 0 || ny >= M || nx >= N ) continue;
			if ( G[nx][ny] == '1' && C[nx][ny] == -1 )
				q.push( make_pair(nx,ny) );
		}
	
		if ( deg[x][y] > 2 ) res = false;
		else if ( res && deg[x][y] < 2 ){
			ext.push_back( make_pair( x , y ) );
		}
	}
	return res;
}

int count_n(int x, int y){
	int nx,ny;
	int res = 0;
	for ( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || ny >= M || nx >= N ) continue;
		if ( G[nx][ny] == '1' ) res++;
	}
	return res;
}

bool extend( int x, int y ){
	int nx,ny;
	for ( int i=0; i < 4; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || ny < 0 || ny >= M || nx >= N ) continue;
		if ( G[nx][ny] == '0' && deg[nx][ny] <= 1 ) return true;
	}
	return false;
}

int main(){
	bool ok;
	while ( cin >> N >> M && N && M ){

		for (int i=0; i < N; ++i)
			for ( int j=0; j < M; ++j ){
				C[i][j] = -1;
				cin >> G[i][j];
			}
				
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < M; ++j )
				deg[i][j] = count_n(i,j);
				
		int res = 0;
		int nc = 0;
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < M; j++ ){
				if ( G[i][j] == '1'  && C[i][j] == -1 ){
					ext.clear();
					ok = bfs( i , j , nc );
					nc++;
					if ( ok ){
					
						for ( int k=0; k < ext.size() && ok; ++k ){
							if ( extend( ext[k].first , ext[k].second ) )
								ok = false;
						}
					
						if ( ok ) res++;
					
					}
					
				}
			}

		cout << res << endl;
	} 

	return 0;
}

