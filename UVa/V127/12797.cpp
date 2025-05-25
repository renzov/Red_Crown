#include<cstdio>
#include<cctype>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 128;

typedef pair< int, int > point;
typedef pair< point, int > state;

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

int N;
map<int, int> D[MAXN][MAXN];
char M[MAXN][MAXN];

inline int get_id( const int &x, const int &y ){
	return islower( M[x][y] )? (M[x][y] - 'a'):(M[x][y] - 'A' + 10);
}

inline bool valid( const int &x, const int &y ){
	return ( x >= 0 && y >= 0 && x < N && y < N );
}

int solve(){
	for ( int i = 0; i < N; ++i )
		scanf("%s", M[i] );
	
	int mask;
	queue<state> Q;
	mask = ( 1 << get_id( 0, 0 ) );
	Q.push( state( point(0, 0), mask ) );
	D[0][0][mask] = 0;

	int x, y;
	int nx, ny, nmask;;
	int idx, inv;

	while ( !Q.empty() ){
		
		x = Q.front().first.first, y = Q.front().first.second;
		mask = Q.front().second;
		Q.pop();
		
		for ( int i = 0; i < 4; ++i ){
			nx = x + dx[i];
			ny = y + dy[i];
			
			if ( !valid( nx, ny ) ) continue;
			idx = get_id( nx, ny );
			if ( idx < 10 )
				inv = idx + 10;
			else 
				inv = idx - 10;
				
			if ( (mask >> inv) & 1 ) continue;
			nmask = mask | ( 1 << idx );

			if ( D[nx][ny].count( nmask ) == 0 ){
				D[nx][ny][nmask] = D[x][y][mask] + 1;
				if ( (nx == (N - 1)) && nx == ny ) return D[nx][ny][nmask];				
				Q.push( state( point( nx, ny ), nmask ) );
			}
		}
	}
	return -2;
}

void clean(){
	for ( int i = 0; i < N; ++i )
		for ( int j = 0; j < N; ++j )
			D[i][j].clear();
}

int main(){
	while ( scanf("%d", &N) == 1 ){
		printf("%d\n",  solve() + 1 );
		clean();
	}
	return 0;
}
