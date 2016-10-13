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

const int MAXN = 20;
const int INF = 3500;
bool ok;
int N;
int val[MAXN][MAXN];
int cnt;

int dx[] = {0,1,0,-1,0};
int dy[] = {0,0,-1,0,1};
int used[100][3];
int color[100];
vector< vector<int> > G;
int X[100];
int Y[100];

bool can_place(int y,int x){
	int nx, ny;
	for ( int i=1; i < 5; ++i ){
		nx = x + dx[i];
		ny = y + dy[i];
		if ( nx < 0 || nx >= N || ny < 0 || ny >= N || val[ny][nx] != INF )
			return false;
	}
	return true;
}

bool backtrack( int idx ){
	if ( idx == cnt ) return true;
	for ( int k=0; k < 3; ++k ){
		if ( used[idx][k] == 0 ){
			color[idx] = k;
			for ( vector<int>::iterator v = G[idx].begin(); v != G[idx].end(); v++ ){
				used[*v][k]++;
			}
			if ( backtrack(idx+1) ) return true;
			for ( vector<int>::iterator v = G[idx].begin(); v != G[idx].end(); v++ ){
				used[*v][k]--;
			}
		}
	}
	return false;
}

void create_graph(){
	G = vector< vector<int> > (cnt);
	int x, y, xx, yy;
	for ( int i=0; i < cnt; ++i ){
		for ( int j=1; j < 5; ++j ){
			x = X[i] + dx[j];
			y = Y[i] + dy[j];
			for ( int d1=-1; d1 <= 1; ++d1 )
				for ( int d2=-1; d2 <= 1; ++d2 ){
					xx = x + d1, yy = y + d2;
					if ( xx >= 0 && xx < N && yy >= 0 && yy < N && val[yy][xx] >= 0 && val[yy][xx] != i ){
						G[i].push_back( val[yy][xx] );
					}
				}
		}
		sort( G[i].begin() , G[i].end() );
		G[i].erase( unique( G[i].begin(), G[i].end() ) , G[i].end() );
	}
}

int main(){

	char M[MAXN][MAXN];
	int runs;

	scanf("%d", &runs);
	for ( int cases = 1; cases <= runs; ++cases ){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%s", M[i]);
			for ( int j=0; j < N; ++j )
				val[i][j] = ( M[i][j] == '.' )? INF:-1; 
		}
		cnt = 0;
		for ( int i=0; i < N; ++i )
			for ( int j=0; j < N; ++j ){
				if ( val[i][j] == INF && can_place(i,j) ){
					val[i][j] = val[i-1][j] = val[i][j+1] = val[i][j-1] = val[i+1][j] = cnt;
					X[cnt] = j, Y[cnt] = i;
					cnt++;
				}
			}
		ok = true;
		for ( int i=0; i < N && ok; ++i )
			ok = (*max_element( val[i], val[i] + N ) != INF);

		if ( ok ){
			create_graph();
			for ( int i=0; i < cnt; ++i ) used[i][0] = used[i][1] = used[i][2] = 0;
			ok &= backtrack( 0 );
			G.clear();
		}
		printf("Case %d:", cases);
		if ( !ok ) puts(" Not Possible!");
		else {
			for ( int i=0; i < cnt; ++i ){
				for ( int j=0; j < 5; ++j ){
					M[ Y[i] + dy[j] ][ X[i] + dx[j] ] = (char)( 'B' + color[i] );	
				}
			}
			puts("");
			for ( int i=0; i < N; ++i ) printf("%s\n", M[i]);
		}
	}
	return 0;
}

